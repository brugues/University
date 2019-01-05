using System.Collections.Generic;

namespace MagicStore.Models
{
    public class ProcessRequest
    {
        public IEnumerable<StockRequest> StockRequest { get; set; }
        public IEnumerable<OwnerInventory> OwnerInventory { get; set; }
    }
}
