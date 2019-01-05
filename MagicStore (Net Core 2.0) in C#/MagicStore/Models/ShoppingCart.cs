using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MagicStore.Models
{
    public class ShoppingCart
    {
        public decimal Price { get; set; }
        public ICollection<StoreInventory> Products { set; get; } = new List<StoreInventory>();
    }
}
