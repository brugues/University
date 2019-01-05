using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Migrations;
using System;
using System.Collections.Generic;

namespace MagicStore.Data.Migrations
{
    public partial class FKUpdate_3 : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropPrimaryKey(
                name: "PK_OwnerInventory",
                table: "OwnerInventory");

            migrationBuilder.AddColumn<int>(
                name: "OwnerInventoryID",
                table: "OwnerInventory",
                nullable: false,
                defaultValue: 0)
                .Annotation("SqlServer:ValueGenerationStrategy", SqlServerValueGenerationStrategy.IdentityColumn);

            migrationBuilder.AddPrimaryKey(
                name: "PK_OwnerInventory",
                table: "OwnerInventory",
                column: "OwnerInventoryID");

            migrationBuilder.CreateIndex(
                name: "IX_OwnerInventory_ProductID",
                table: "OwnerInventory",
                column: "ProductID");
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropPrimaryKey(
                name: "PK_OwnerInventory",
                table: "OwnerInventory");

            migrationBuilder.DropIndex(
                name: "IX_OwnerInventory_ProductID",
                table: "OwnerInventory");

            migrationBuilder.DropColumn(
                name: "OwnerInventoryID",
                table: "OwnerInventory");

            migrationBuilder.AddPrimaryKey(
                name: "PK_OwnerInventory",
                table: "OwnerInventory",
                column: "ProductID");
        }
    }
}
