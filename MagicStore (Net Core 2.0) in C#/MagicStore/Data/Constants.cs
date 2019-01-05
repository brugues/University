using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MagicStore.Data
{
    public static class Constants
    {
        public const string OwnerRole = "OwnerRole";
        public const string FranchiseHolderRole = "FranchiseRole";
        public const string CustomerRole = "CustomerRole";
    }

    public class FranchiseHolderStores
    {
        public static Dictionary<string, int> Stores = new Dictionary<string, int>()
        {
            {"s3676997@student.rmit.edu.au", 2 }
        };
    }
}
