using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;
using MagicStore.Models;

namespace MagicStore.Data
{
    public class ApplicationDbContext : IdentityDbContext<ApplicationUser>
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {
        }

        public DbSet<Product> Products { get; set; }
        public DbSet<Store> Stores { get; set; }
        public DbSet<OwnerInventory> OwnerInventory { get; set; }
        public DbSet<StockRequest> StockRequests { get; set; }
        public DbSet<StoreInventory> StoreInventories { get; set; }
        public DbSet<Order> Orders { get; set; }

        protected override void OnModelCreating(ModelBuilder builder)
        {
            base.OnModelCreating(builder);
            // Customize the ASP.NET Identity model and override the defaults if needed.
            // For example, you can rename the ASP.NET Identity table names and more.
            // Add your customizations after calling base.OnModelCreating(builder);

            builder.Entity<Product>().ToTable("Products");
            builder.Entity<Store>().ToTable("Stores");
            builder.Entity<OwnerInventory>().ToTable("OwnerInventory");
            builder.Entity<StockRequest>().ToTable("StockRequests");
            builder.Entity<StoreInventory>().ToTable("StoreInventories");
            builder.Entity<StoreInventory>().HasKey(x => new { x.StoreID, x.ProductID });
            builder.Entity<Order>().ToTable("Orders");
            builder.Entity<ProductOrder>().ToTable("ProductOrder");
            builder.Entity<ProductOrder>().HasKey(x => new { x.OrderID, x.ProductID });
        }
    }
}
