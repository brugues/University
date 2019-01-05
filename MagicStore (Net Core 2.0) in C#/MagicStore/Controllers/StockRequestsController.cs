using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using MagicStore.Data;
using MagicStore.Models;

namespace MagicStore.Controllers
{
    public class StockRequestsController : Controller
    {
        private readonly ApplicationDbContext _context;

        public StockRequestsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // This method displays all the stock requests made to the owner.
        public IActionResult Index()
        {
            IEnumerable<StockRequest> stock =  _context.StockRequests.Include(s => s.Product).Include(s => s.Store);
            IEnumerable<OwnerInventory> owner = _context.OwnerInventory.ToList();

            ProcessRequest process = new ProcessRequest
            {
                StockRequest = stock,
                OwnerInventory = owner
            };

            return View(process);
        }

        //This method displays gets the details of the stock request that matches the given ID.
        public async Task<IActionResult> Details(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var stockRequest = await _context.StockRequests
                .Include(s => s.Product)
                .Include(s => s.Store)
                .SingleOrDefaultAsync(m => m.StockRequestID == id);
            if (stockRequest == null)
            {
                return NotFound();
            }

            return View(stockRequest);
        }

        //This method process the request. That is, id updates the database with the new product for the store,
        //or the new stock level for the product. The details are all in the stock request that matches the
        //given ID.
        public async Task<IActionResult> Process(int? id)
        {
            if (id != null)
            {
                StockRequest RequestToDelete = (StockRequest) _context.StockRequests.Include(s => s.Store).Include(s => s.Product).Where(x => x.StockRequestID.Equals((int)id)).First();

                OwnerInventory OwnerInventoryEntry = (OwnerInventory) _context.OwnerInventory.Where(x => x.ProductID.Equals(RequestToDelete.ProductID)).First();
                OwnerInventoryEntry.StockLevel = OwnerInventoryEntry.StockLevel - RequestToDelete.Quantity;

                StoreInventory StoreInventoryEntry = (StoreInventory)_context.StoreInventories.Where(x => x.StoreID.Equals(RequestToDelete.StoreID)).Where(x => x.ProductID.Equals(RequestToDelete.ProductID)).FirstOrDefault();

                if (ModelState.IsValid)
                {
                    try
                    {
                        _context.StockRequests.Remove(RequestToDelete);
                        _context.Update(OwnerInventoryEntry);

                        if(StoreInventoryEntry == null)
                        {
                            StoreInventoryEntry = new StoreInventory
                            {
                                StoreID = RequestToDelete.StoreID,
                                ProductID = RequestToDelete.ProductID,
                                StockLevel = RequestToDelete.Quantity
                            };
                            _context.Add(StoreInventoryEntry);
                        }
                        else
                        {
                            StoreInventoryEntry.StockLevel += RequestToDelete.Quantity;
                            _context.Update(StoreInventoryEntry);
                        }

                        await _context.SaveChangesAsync();
                    }
                    catch (DbUpdateConcurrencyException)
                    {
                        
                    }
                    return RedirectToAction(nameof(Index));
                }
            }

            return View();
        }

        //This view creates a new StockRequest with the product that matches the ID and the store that
        //matches the given StoreID.
        public async Task<IActionResult> Create(int? id, int? store)
        {
            try
            {
                StockRequest request = new StockRequest();
                request.Quantity = 1;
                request.StoreID = (int)store;
                request.ProductID = (int)id;
                _context.Add(request);

                await _context.SaveChangesAsync();

                ViewData["ProductName"] = _context.Products.Where(x => x.ProductID.Equals(id)).First().Name;
                ViewData["StoreName"] = _context.Stores.Where(x => x.StoreID.Equals(store)).First().Name;
                ViewData["Quantity"] = 1;
            }
            catch (Exception)
            {
                Console.Write("Exception caught");
            }

            return View();
        }

        // This method creates a new stock request with the quantity set to the threshold chosen by the
        // franchise holder.
        public async Task<IActionResult> CreateThreshold(int? id, int? store, int threshold)
        {
            try
            {
                StockRequest request = new StockRequest();
                request.Quantity = threshold;
                request.StoreID = (int)store;
                request.ProductID = (int)id;
                _context.Add(request);

                await _context.SaveChangesAsync();

                ViewData["ProductName"] = _context.Products.Where(x => x.ProductID.Equals(id)).First().Name;
                ViewData["StoreName"] = _context.Stores.Where(x => x.StoreID.Equals(store)).First().Name;
                ViewData["Quantity"] = threshold;
            }
            catch (Exception)
            {
                Console.Write("Exception caught");
            }
            
            return View("Create");
        }

        //This method returns the view for the franchise holder to introduce a threshold, so that he/she
        // can check the products that match the threshold.
        public IActionResult ThresholdInput()
        {
            return View();
        }
    }
}
