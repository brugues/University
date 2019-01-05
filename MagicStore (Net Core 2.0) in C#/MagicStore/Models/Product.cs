using System;
using System.ComponentModel.DataAnnotations;

namespace MagicStore.Models
{
    public class Product
    {
        [Key, Display(Name = "Product ID")]
        public int ProductID { get; set; }
        [Display(Name = "Product Name")]
        public string Name { get; set; }
        public decimal Price { get; set; }
    }
}
