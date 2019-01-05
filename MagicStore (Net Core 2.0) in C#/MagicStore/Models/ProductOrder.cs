using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Threading.Tasks;

namespace MagicStore.Models
{
    public class ProductOrder
    {
        [ForeignKey("Product"), Display(Name = "Product ID")]
        public int ProductID { get; set; }
        public Product Product { get; set; }

        [ForeignKey("Store"), Display(Name = "Store ID")]
        public int StoreID { get; set; }
        public Store Store { get; set; }

        [ForeignKey("Order"), Display(Name = "Order ID")]
        public int OrderID { get; set;}
        public Order Order { get; set; }

        public int Quantity { get; set; }
    }
}
