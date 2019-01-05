using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace MagicStore.Models
{
    public class Order
    {
        [Key]
        public int OrderID { get; set; }
        public string CustomerID { get; set; }
        public decimal Price { get; set; }
        [Display(Name = "Date")]
        public DateTime Datetime { get; set; }
        public ICollection<ProductOrder> Products { set; get; } = new List<ProductOrder>();
    }
}
