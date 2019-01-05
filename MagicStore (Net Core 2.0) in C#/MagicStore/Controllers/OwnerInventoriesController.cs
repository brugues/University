using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using MagicStore.Data;
using MagicStore.Models;
using Microsoft.AspNetCore.Authorization;

namespace MagicStore.Controllers
{
    public class OwnerInventoriesController : Controller
    {
        private readonly ApplicationDbContext _context;

        public OwnerInventoriesController(ApplicationDbContext context)
        {
            _context = context;
        }

        // This method returns a view with the owner inventory (and all its products).
        [Authorize(Roles = Constants.OwnerRole)]
        public async Task<IActionResult> Index()
        {
            var applicationDbContext = _context.OwnerInventory.Include(o => o.Product);
            return View(await applicationDbContext.ToListAsync());
        }

        // This method gets the product details (in the onwer's inventory)
        // of the product that matches the given ID.
        public async Task<IActionResult> Details(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var ownerInventory = await _context.OwnerInventory
                .Include(o => o.Product)
                .SingleOrDefaultAsync(m => m.ProductID == id);
            if (ownerInventory == null)
            {
                return NotFound();
            }

            return View(ownerInventory);
        }

        //This view returns the view that is used by the owner to reset a certain product stock
        // (the one that matches the given ID).
        public async Task<IActionResult> Reset(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var inventory = await _context.OwnerInventory.Include(p => p.Product).SingleOrDefaultAsync(m => m.ProductID == id);
            if (inventory == null)
            {
                return NotFound();
            }

            ViewData["ProductName"] = inventory.Product.Name;
            ViewData["ProductID"] = inventory.ProductID;

            return View(inventory);
        }

        // This product reset's the product stock of the product that matches the given ID.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Reset(int id, [Bind("ProductID,StockLevel")] OwnerInventory ownerInventory)
        {
            if (id != ownerInventory.ProductID)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _context.Update(ownerInventory);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!OwnerInventoryExists(ownerInventory.ProductID))
                    {
                        return NotFound();
                    }
                    else
                    {
                        throw;
                    }
                }
                return RedirectToAction(nameof(Index));
            }

            var inventory = _context.OwnerInventory.Include(x => x.Product)
                .Where(x => x.ProductID.Equals(ownerInventory.ProductID))
                .Where(x => x.StockLevel.Equals(ownerInventory.StockLevel)).FirstOrDefault();

            return View(inventory);
        }

        //This product makes sure that the product exists in the database.
        private bool OwnerInventoryExists(int id)
        {
            return _context.OwnerInventory.Any(e => e.ProductID == id);
        }
    }
}