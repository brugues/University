using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.EntityFrameworkCore;
using System.Threading.Tasks;
using MagicStore.Data;
using Microsoft.AspNetCore.Authorization;
using MagicStore.Models;
using MagicStore.Extensions;
using Microsoft.AspNetCore.Http;
using Newtonsoft.Json;

namespace MagicStore.Controllers
{
    /// <summary>
    /// This class contains the methods for the Customer Controller
    /// </summary>
    [Authorize(Roles = Constants.CustomerRole)]
    public class CustomerController : Controller
    {
        public ICollection<ProductOrder> SessionOrder { get; set; }
        private String Key = "ShoppingCart";
        private readonly ApplicationDbContext _context;

        public CustomerController(ApplicationDbContext context)
        {
            SessionOrder = new List<ProductOrder>();
            _context = context;
        }

        // This method adds a certain product into the Customer's shopping cart.
        public IActionResult AddToCart(int id, int store)
        {
            var inventory = (StoreInventory) _context.StoreInventories.Where(x => x.ProductID.Equals(id)).Where(x => x.StoreID.Equals(store)).Include(x => x.Product).Include(x => x.Store).First();

            String str;

            if (HttpContext.Session.Keys.Contains(Key))
            {
                str = HttpContext.Session.GetString(Key);
                this.SessionOrder = JsonConvert.DeserializeObject<List<ProductOrder>>(str, new JsonSerializerSettings()
                {
                    ReferenceLoopHandling = ReferenceLoopHandling.Ignore
                });
            }

            inventory.StockLevel = 1;

            ProductOrder newProduct = new ProductOrder();
            newProduct.StoreID = inventory.StoreID;
            newProduct.Store = inventory.Store;
            newProduct.Product = inventory.Product;
            newProduct.ProductID = inventory.ProductID;

            bool match = false;

            //Check if the product is already on the shopping cart. If so, we increment the product's quantity.
            foreach(var productorder in this.SessionOrder)
            {
                if(productorder.StoreID == newProduct.StoreID && productorder.ProductID == newProduct.ProductID)
                {
                    productorder.Quantity += 1;
                    match = true;
                }
            }

            if (!match)
            {
                newProduct.Quantity = 1;
                this.SessionOrder.Add(newProduct);
            }

            //Store the modified shopping cart in the session variable.
            str = JsonConvert.SerializeObject(this.SessionOrder, new JsonSerializerSettings()
            {
                ReferenceLoopHandling = ReferenceLoopHandling.Ignore
            });
            HttpContext.Session.SetString(Key, str);

            return View();
        }

        // This method returns the view for the customer's order history.
        public IActionResult Orders()
        {
            return View("OrderHistory");
        }

        //This method deletes a product from the customer's shopping cart.
        public IActionResult DeleteProduct(int id)
        {
            var str = HttpContext.Session.GetString(Key);
            this.SessionOrder = JsonConvert.DeserializeObject<List<ProductOrder>>(str, new JsonSerializerSettings()
            {
                ReferenceLoopHandling = ReferenceLoopHandling.Ignore
            });

            var toRemove = SessionOrder.Where(x => x.ProductID.Equals(id)).FirstOrDefault();
            SessionOrder.Remove(toRemove);

            str = JsonConvert.SerializeObject(this.SessionOrder, new JsonSerializerSettings()
            {
                ReferenceLoopHandling = ReferenceLoopHandling.Ignore
            });
            HttpContext.Session.SetString(Key, str);

            return RedirectToAction("ShoppingCart");
        }

        //This method returns the view that displays the checkout process to the user.
        public IActionResult Checkout()
        {
            return View();
        }

        //This method returns the customer's main view.
        public IActionResult Index() => View();

        public async Task<IActionResult> OrderDetails(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var order = await _context.Orders.Where(x => x.OrderID.Equals(id))
                .Include(x => x.Products)
                .ThenInclude(y => y.Product)
                .Include(x => x.Products)
                .ThenInclude(y => y.Store)
                .FirstOrDefaultAsync();

            if (order == null)
            {
                return NotFound();
            }

            ViewData["Price"] = order.Price;

            return View(order);
        }

        //This method updates the database (store inventory, new order) once the order has been completed.
        public async Task<IActionResult> FinishOrder()
        {
            Order newOrder = new Order();

            var str = HttpContext.Session.GetString(Key);
            this.SessionOrder = JsonConvert.DeserializeObject<List<ProductOrder>>(str, new JsonSerializerSettings()
            {
                ReferenceLoopHandling = ReferenceLoopHandling.Ignore
            });

            newOrder.Products = this.SessionOrder;

            bool allProductsAreValid = true;

            //Check if there's still stock for the products in the shopping cart. 
            foreach(var product in newOrder.Products)
            {
                var inventory = (StoreInventory) await _context.StoreInventories.Where(x => x.ProductID.Equals(product.ProductID))
                    .Where(x => x.StoreID.Equals(product.StoreID)).Include(x => x.Product).Include(x => x.Store).FirstAsync();

                if (inventory.StockLevel < product.Quantity){
                    allProductsAreValid = false;
                }
            }

            if (allProductsAreValid)
            {
                decimal price = 0;
                newOrder.Datetime = DateTime.Now.Date;
                newOrder.CustomerID = User.getUserId();

                //Update each product stock in the database
                foreach(var product in newOrder.Products)
                {
                    int i = product.Quantity;
                    while (i > 0)
                    {
                        price += product.Product.Price;
                        i--;
                    }
                    
                    var inventory = (StoreInventory) await _context.StoreInventories.Where(x => x.ProductID.Equals(product.ProductID))
                        .Where(x => x.StoreID.Equals(product.StoreID)).Include(x => x.Product).Include(x => x.Store).FirstAsync();
                    inventory.StockLevel -= product.Quantity;
                    _context.Update(inventory);
                }

                newOrder.Price = price;
                Order order = newOrder;
                await _context.AddAsync(newOrder);

                await _context.SaveChangesAsync();

                ViewData["OrderID"] = newOrder.OrderID;
                ViewData["Price"] = newOrder.Price;

                //We empty the session order, since the order has been finalised. 
                this.SessionOrder = new List<ProductOrder>();
                str = JsonConvert.SerializeObject(this.SessionOrder, new JsonSerializerSettings()
                {
                    ReferenceLoopHandling = ReferenceLoopHandling.Ignore
                });
                HttpContext.Session.SetString(Key, str);

                return View("OrderDetails", order);
            }
            else
            {
                return View("NotEnoughStock");
            }
        }

        //This method acts as a web api, and gets the customer's order history, and returns it in JSON format.
        [Route("Customer/OrderHistory")]
        [HttpGet]
        public IEnumerable<Order> OrderHistory()
        {
            string userID = User.getUserId();

            var orderHistory = _context.Orders.Where(x => x.CustomerID.Equals(userID)).ToList();

            return orderHistory;
        }

        //This method displays the shopping cart to the user with all its products.
        public IActionResult ShoppingCart()
        {
            var str = HttpContext.Session.GetString(Key);

            if (str != null)
            {
                this.SessionOrder = JsonConvert.DeserializeObject<List<ProductOrder>>(str, new JsonSerializerSettings()
                {
                    ReferenceLoopHandling = ReferenceLoopHandling.Ignore
                });
            }

            return View(this.SessionOrder);
        }
    }
}