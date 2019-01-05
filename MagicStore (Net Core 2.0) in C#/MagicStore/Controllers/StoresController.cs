using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using MagicStore.Data;

namespace MagicStore.Controllers
{
    public class StoresController : Controller
    {
        private readonly ApplicationDbContext _context;

        public StoresController(ApplicationDbContext context)
        {
            _context = context;
        }

        // This method returns a list of all the available stores.
        public async Task<IActionResult> Index()
        {
            return View(await _context.Stores.ToListAsync());
        }
    }
}
