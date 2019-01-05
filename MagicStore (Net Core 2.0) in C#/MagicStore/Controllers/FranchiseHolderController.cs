using Microsoft.AspNetCore.Mvc;
using MagicStore.Data;
using Microsoft.AspNetCore.Authorization;

namespace MagicStore.Controllers
{
    [Authorize(Roles = Constants.FranchiseHolderRole)]
    public class FranchiseHolderController : Controller
    {
        //This method returns the main menu to the franchise holder.
        public IActionResult Index()
        {
            return View();
        }
    }
}
