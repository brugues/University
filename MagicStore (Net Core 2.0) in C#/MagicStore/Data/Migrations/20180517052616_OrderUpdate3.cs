using Microsoft.EntityFrameworkCore.Migrations;
using System;
using System.Collections.Generic;

namespace MagicStore.Data.Migrations
{
    public partial class OrderUpdate3 : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<int>(
                name: "StoreID",
                table: "ProductOrder",
                nullable: false,
                defaultValue: 0);

            migrationBuilder.CreateIndex(
                name: "IX_ProductOrder_StoreID",
                table: "ProductOrder",
                column: "StoreID");

            migrationBuilder.AddForeignKey(
                name: "FK_ProductOrder_Stores_StoreID",
                table: "ProductOrder",
                column: "StoreID",
                principalTable: "Stores",
                principalColumn: "StoreID",
                onDelete: ReferentialAction.Cascade);
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_ProductOrder_Stores_StoreID",
                table: "ProductOrder");

            migrationBuilder.DropIndex(
                name: "IX_ProductOrder_StoreID",
                table: "ProductOrder");

            migrationBuilder.DropColumn(
                name: "StoreID",
                table: "ProductOrder");
        }
    }
}
