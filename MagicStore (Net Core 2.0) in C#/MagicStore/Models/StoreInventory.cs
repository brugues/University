using System;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace MagicStore.Models
{
    public class StoreInventory
    {
        [ForeignKey("Store"), Display(Name = "Store ID")]
        public int StoreID { get; set; }
        public Store Store { get; set; }
        [ForeignKey("Product"), Display(Name = "Product ID")]
        public int ProductID { get; set; }
        public Product Product { get; set; }
        [Range(0, 100000)]
        public int StockLevel { get; set; }
    }
}
