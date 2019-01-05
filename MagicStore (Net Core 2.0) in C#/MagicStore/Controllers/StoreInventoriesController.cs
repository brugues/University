using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using MagicStore.Data;
using MagicStore.Models;

namespace MagicStore.Controllers
{
    public class StoreInventoriesController : Controller
    {
        private readonly ApplicationDbContext _context;

        public StoreInventoriesController(ApplicationDbContext context)
        {
            _context = context;
        }

        // This method returns the paginated store inventory (3 products per page). It also supports
        // search method to filter the products.
        public async Task<IActionResult> Index(int? id, string search, int? page)
        {
            IQueryable<StoreInventory> applicationDbContext;
            int pageSize = 3;

            //If store is specified (this matches the customer role).
            if (id != null)
            {
                if (search != null)
                {
                    page = 1;
                }
                else
                {
                    search = "all";
                }

                try
                {
                    if (search.Equals("all"))
                    {
                        applicationDbContext = _context.StoreInventories.Include(s => s.Product).Include(s => s.Store).Where(s => s.StoreID.Equals(id));
                    }
                    else
                    {
                        applicationDbContext = _context.StoreInventories.Include(s => s.Product).Include(s => s.Store).Where(s => s.StoreID.Equals(id)).Where(s => s.Product.Name.Contains(search));
                    }
                }
                catch (NullReferenceException)
                {
                    applicationDbContext = _context.StoreInventories.Include(s => s.Product).Include(s => s.Store).Where(s => s.StoreID.Equals(id));
                }
            }
            // If store is not specified (this matches the franchise holder role)
            else
            {
                if (search != null)
                {
                    page = 1;
                }
                else
                {
                    search = "all";
                }

                try
                {
                    if (search.Equals("all"))
                    {
                        applicationDbContext = _context.StoreInventories
                        .Include(s => s.Product)
                        .Where(s => s.StockLevel > 0)
                        .Include(s => s.Store)
                        .Where(s => s.StoreID.Equals(FranchiseHolderStores.Stores[User.Identity.Name]));
                    }
                    else
                    {
                        applicationDbContext = _context.StoreInventories
                       .Include(s => s.Product)
                       .Where(s => s.StockLevel > 0)
                       .Include(s => s.Store)
                       .Where(s => s.StoreID.Equals(FranchiseHolderStores.Stores[User.Identity.Name]))
                       .Where(s => s.Product.Name.Contains(search));
                    }
                }
                catch (NullReferenceException)
                {
                    applicationDbContext = _context.StoreInventories
                        .Include(s => s.Product)
                        .Where(s => s.StockLevel > 0)
                        .Include(s => s.Store)
                        .Where(s => s.StoreID.Equals(FranchiseHolderStores.Stores[User.Identity.Name]));
                }

                

                
            }

            return View(await PaginatedList<StoreInventory>.CreateAsync(applicationDbContext.AsNoTracking(), page ?? 1, pageSize));
        }

        //This method returns the products that are not part of the store but can be found in the owner's
        // inventory.
        public IActionResult IndexNotInStore()
        {
            var applicationDbContext = _context.OwnerInventory.Include(p => p.Product)
                                        .FromSql("SELECT * FROM OwnerInventory WHERE ProductID IN (SELECT OwnerInventory.ProductID FROM dbo.OwnerInventory EXCEPT SELECT StoreInventories.ProductID FROM dbo.StoreInventories WHERE StoreID={0} AND StockLevel > 0)", FranchiseHolderStores.Stores[User.Identity.Name])
                                        .ToList();

            return View(applicationDbContext);
        }

        public async Task<IActionResult> IndexThreshold(ThresholdInput t)
        {
            int threshold = t.Threshold;
            ViewData["threshold"] = threshold;
            var applicationDbContext = _context.StoreInventories.Include(s => s.Product).Include(s => s.Store).Where(s => s.StockLevel < threshold).Where(s => s.StoreID.Equals(FranchiseHolderStores.Stores[User.Identity.Name]));
            return View(await applicationDbContext.ToListAsync());
        }

        // This method displays the details of a certain product in a certain store.
        public async Task<IActionResult> Details(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var storeInventory = await _context.StoreInventories
                .Include(s => s.Product)
                .Include(s => s.Store)
                .SingleOrDefaultAsync(m => m.StoreID == id);
            if (storeInventory == null)
            {
                return NotFound();
            }

            return View(storeInventory);
        }

        //This method checks if the store inventory actually exists.
        private bool StoreInventoryExists(int id)
        {
            return _context.StoreInventories.Any(e => e.StoreID == id);
        }
    }

    /// <summary>
    /// This class handles all the paginated list functionality
    /// </summary>
    /// <typeparam name="T"></typeparam>
    public class PaginatedList<T> : List<T>
    {
        public int PageIndex { get; private set; }
        public int TotalPages { get; private set; }

        //Constructor of the class.
        public PaginatedList(List<T> items, int count, int pageIndex, int pageSize)
        {
            PageIndex = pageIndex;
            TotalPages = (int)Math.Ceiling(count / (double)pageSize);

            this.AddRange(items);
        }

        //This method checks if the current page has a previous page
        public bool HasPreviousPage
        {
            get
            {
                return (PageIndex > 1);
            }
        }

        //This method checks if the current page has another page after.
        public bool HasNextPage
        {
            get
            {
                return (PageIndex < TotalPages);
            }
        }


        //This method creates a new paginated list with the given data, the page size and the page index.
        public static async Task<PaginatedList<T>> CreateAsync(IQueryable<T> source, int pageIndex, int pageSize)
        {
            var count = await source.CountAsync();
            var items = await source.Skip((pageIndex - 1) * pageSize).Take(pageSize).ToListAsync();
            return new PaginatedList<T>(items, count, pageIndex, pageSize);
        }
    }
}
