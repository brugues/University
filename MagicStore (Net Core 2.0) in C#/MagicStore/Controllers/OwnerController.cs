using Microsoft.AspNetCore.Mvc;
using MagicStore.Data;
using Microsoft.AspNetCore.Authorization;

namespace MagicStore.Controllers
{
    [Authorize(Roles = Constants.OwnerRole)]
    public class OwnerController : Controller
    {
        //This method returns the Owner's main menu.
        public IActionResult Index()
        {
            return View();
        }
    }
}
