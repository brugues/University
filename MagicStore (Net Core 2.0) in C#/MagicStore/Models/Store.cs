using System;
using System.Collections.Generic;
namespace MagicStore.Models
{
    public class Store
    {
        public int StoreID { get; set; }
        public string Name { get; set; }
        public ICollection<StoreInventory> StoreInventory { get; } = new List<StoreInventory>();
    }
}
