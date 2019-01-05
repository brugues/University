using System.Diagnostics;
using Microsoft.AspNetCore.Mvc;
using MagicStore.Models;

namespace MagicStore.Controllers
{
    public class HomeController : Controller
    {
        //This method returns the homepage view of the application
        public IActionResult Index()
        {
            return View();
        }

        //This method returns the error page view of the application
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }
    }
}
