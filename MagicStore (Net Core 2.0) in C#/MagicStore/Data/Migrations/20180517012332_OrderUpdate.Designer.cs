﻿// <auto-generated />
using MagicStore.Data;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Migrations;
using Microsoft.EntityFrameworkCore.Storage;
using Microsoft.EntityFrameworkCore.Storage.Internal;
using System;

namespace MagicStore.Data.Migrations
{
    [DbContext(typeof(ApplicationDbContext))]
    [Migration("20180517012332_OrderUpdate")]
    partial class OrderUpdate
    {
        protected override void BuildTargetModel(ModelBuilder modelBuilder)
        {
#pragma warning disable 612, 618
            modelBuilder
                .HasAnnotation("ProductVersion", "2.0.2-rtm-10011")
                .HasAnnotation("SqlServer:ValueGenerationStrategy", SqlServerValueGenerationStrategy.IdentityColumn);

            modelBuilder.Entity("MagicStore.Models.ApplicationUser", b =>
                {
                    b.Property<string>("Id")
                        .ValueGeneratedOnAdd();

                    b.Property<int>("AccessFailedCount");

                    b.Property<string>("ConcurrencyStamp")
                        .IsConcurrencyToken();

                    b.Property<string>("Email")
                        .HasMaxLength(256);

                    b.Property<bool>("EmailConfirmed");

                    b.Property<bool>("LockoutEnabled");

                    b.Property<DateTimeOffset?>("LockoutEnd");

                    b.Property<string>("NormalizedEmail")
                        .HasMaxLength(256);

                    b.Property<string>("NormalizedUserName")
                        .HasMaxLength(256);

                    b.Property<string>("PasswordHash");

                    b.Property<string>("PhoneNumber");

                    b.Property<bool>("PhoneNumberConfirmed");

                    b.Property<string>("SecurityStamp");

                    b.Property<bool>("TwoFactorEnabled");

                    b.Property<string>("UserName")
                        .HasMaxLength(256);

                    b.HasKey("Id");

                    b.HasIndex("NormalizedEmail")
                        .HasName("EmailIndex");

                    b.HasIndex("NormalizedUserName")
                        .IsUnique()
                        .HasName("UserNameIndex")
                        .HasFilter("[NormalizedUserName] IS NOT NULL");

                    b.ToTable("AspNetUsers");
                });

            modelBuilder.Entity("MagicStore.Models.Order", b =>
                {
                    b.Property<int>("OrderID")
                        .ValueGeneratedOnAdd();

                    b.Property<string>("CustomerID");

                    b.Property<decimal>("Price");

                    b.HasKey("OrderID");

                    b.ToTable("Orders");
                });

            modelBuilder.Entity("MagicStore.Models.OwnerInventory", b =>
                {
                    b.Property<int>("ProductID");

                    b.Property<int>("StockLevel");

                    b.HasKey("ProductID");

                    b.ToTable("OwnerInventory");
                });

            modelBuilder.Entity("MagicStore.Models.Product", b =>
                {
                    b.Property<int>("ProductID")
                        .ValueGeneratedOnAdd();

                    b.Property<string>("Name");

                    b.Property<int?>("OrderID");

                    b.Property<decimal>("Price");

                    b.HasKey("ProductID");

                    b.HasIndex("OrderID");

                    b.ToTable("Products");
                });

            modelBuilder.Entity("MagicStore.Models.StockRequest", b =>
                {
                    b.Property<int>("StockRequestID")
                        .ValueGeneratedOnAdd();

                    b.Property<int>("ProductID");

                    b.Property<int>("Quantity");

                    b.Property<int>("StoreID");

                    b.HasKey("StockRequestID");

                    b.HasIndex("ProductID");

                    b.HasIndex("StoreID");

                    b.ToTable("StockRequests");
                });

            modelBuilder.Entity("MagicStore.Models.Store", b =>
                {
                    b.Property<int>("StoreID")
                        .ValueGeneratedOnAdd();

                    b.Property<string>("Name");

                    b.HasKey("StoreID");

                    b.ToTable("Stores");
                });

            modelBuilder.Entity("MagicStore.Models.StoreInventory", b =>
                {
                    b.Property<int>("StoreID");

                    b.Property<int>("ProductID");

                    b.Property<int>("StockLevel");

                    b.HasKey("StoreID", "ProductID");

                    b.HasIndex("ProductID");

                    b.ToTable("StoreInventories");
                });

            modelBuilder.Entity("Microsoft.AspNetCore.Identity.IdentityRole", b =>
                {
                    b.Property<string>("Id")
                        .ValueGeneratedOnAdd();

                    b.Property<string>("ConcurrencyStamp")
                        .IsConcurrencyToken();

                    b.Property<string>("Name")
                        .HasMaxLength(256);

                    b.Property<string>("NormalizedName")
                        .HasMaxLength(256);

                    b.HasKey("Id");

                    b.HasIndex("NormalizedName")
                        .IsUnique()
                        .HasName("RoleNameIndex")
                        .HasFilter("[NormalizedName] IS NOT NULL");

                    b.ToTable("AspNetRoles");
                });

            modelBuilder.Entity("Microsoft.AspNetCore.Identity.IdentityRoleClaim<string>", b =>
                {
                    b.Property<int>("Id")
                        .ValueGeneratedOnAdd();

                    b.Property<string>("ClaimType");

                    b.Property<string>("ClaimValue");

                    b.Property<string>("RoleId")
                        .IsRequired();

                    b.HasKey("Id");

                    b.HasIndex("RoleId");

                    b.ToTable("AspNetRoleClaims");
                });

            modelBuilder.Entity("Microsoft.AspNetCore.Identity.IdentityUserClaim<string>", b =>
                {
                    b.Property<int>("Id")
                        .ValueGeneratedOnAdd();

                    b.Property<string>("ClaimType");

                    b.Property<string>("ClaimValue");

                    b.Property<string>("UserId")
                        .IsRequired();

                    b.HasKey("Id");

                    b.HasIndex("UserId");

                    b.ToTable("AspNetUserClaims");
                });

            modelBuilder.Entity("Microsoft.AspNetCore.Identity.IdentityUserLogin<string>", b =>
                {
                    b.Property<string>("LoginProvider");

                    b.Property<string>("ProviderKey");

                    b.Property<string>("ProviderDisplayName");

                    b.Property<string>("UserId")
                        .IsRequired();

                    b.HasKey("LoginProvider", "ProviderKey");

                    b.HasIndex("UserId");

                    b.ToTable("AspNetUserLogins");
                });

            modelBuilder.Entity("Microsoft.AspNetCore.Identity.IdentityUserRole<string>", b =>
                {
                    b.Property<string>("UserId");

                    b.Property<string>("RoleId");

                    b.HasKey("UserId", "RoleId");

                    b.HasIndex("RoleId");

                    b.ToTable("AspNetUserRoles");
                });

            modelBuilder.Entity("Microsoft.AspNetCore.Identity.IdentityUserToken<string>", b =>
                {
                    b.Property<string>("UserId");

                    b.Property<string>("LoginProvider");

                    b.Property<string>("Name");

                    b.Property<string>("Value");

                    b.HasKey("UserId", "LoginProvider", "Name");

                    b.ToTable("AspNetUserTokens");
                });

            modelBuilder.Entity("MagicStore.Models.OwnerInventory", b =>
                {
                    b.HasOne("MagicStore.Models.Product", "Product")
                        .WithMany()
                        .HasForeignKey("ProductID")
                        .OnDelete(DeleteBehavior.Cascade);
                });

            modelBuilder.Entity("MagicStore.Models.Product", b =>
                {
                    b.HasOne("MagicStore.Models.Order")
                        .WithMany("Products")
                        .HasForeignKey("OrderID");
                });

            modelBuilder.Entity("MagicStore.Models.StockRequest", b =>
                {
                    b.HasOne("MagicStore.Models.Product", "Product")
                        .WithMany()
                        .HasForeignKey("ProductID")
                        .OnDelete(DeleteBehavior.Cascade);

                    b.HasOne("MagicStore.Models.Store", "Store")
                        .WithMany()
                        .HasForeignKey("StoreID")
                        .OnDelete(DeleteBehavior.Cascade);
                });

            modelBuilder.Entity("MagicStore.Models.StoreInventory", b =>
                {
                    b.HasOne("MagicStore.Models.Product", "Product")
                        .WithMany()
                        .HasForeignKey("ProductID")
                        .OnDelete(DeleteBehavior.Cascade);

                    b.HasOne("MagicStore.Models.Store", "Store")
                        .WithMany("StoreInventory")
                        .HasForeignKey("StoreID")
                        .OnDelete(DeleteBehavior.Cascade);
                });

            modelBuilder.Entity("Microsoft.AspNetCore.Identity.IdentityRoleClaim<string>", b =>
                {
                    b.HasOne("Microsoft.AspNetCore.Identity.IdentityRole")
                        .WithMany()
                        .HasForeignKey("RoleId")
                        .OnDelete(DeleteBehavior.Cascade);
                });

            modelBuilder.Entity("Microsoft.AspNetCore.Identity.IdentityUserClaim<string>", b =>
                {
                    b.HasOne("MagicStore.Models.ApplicationUser")
                        .WithMany()
                        .HasForeignKey("UserId")
                        .OnDelete(DeleteBehavior.Cascade);
                });

            modelBuilder.Entity("Microsoft.AspNetCore.Identity.IdentityUserLogin<string>", b =>
                {
                    b.HasOne("MagicStore.Models.ApplicationUser")
                        .WithMany()
                        .HasForeignKey("UserId")
                        .OnDelete(DeleteBehavior.Cascade);
                });

            modelBuilder.Entity("Microsoft.AspNetCore.Identity.IdentityUserRole<string>", b =>
                {
                    b.HasOne("Microsoft.AspNetCore.Identity.IdentityRole")
                        .WithMany()
                        .HasForeignKey("RoleId")
                        .OnDelete(DeleteBehavior.Cascade);

                    b.HasOne("MagicStore.Models.ApplicationUser")
                        .WithMany()
                        .HasForeignKey("UserId")
                        .OnDelete(DeleteBehavior.Cascade);
                });

            modelBuilder.Entity("Microsoft.AspNetCore.Identity.IdentityUserToken<string>", b =>
                {
                    b.HasOne("MagicStore.Models.ApplicationUser")
                        .WithMany()
                        .HasForeignKey("UserId")
                        .OnDelete(DeleteBehavior.Cascade);
                });
#pragma warning restore 612, 618
        }
    }
}
