using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace MagicStore.Models
{
    public class ThresholdInput
    {
        [Required]
        public int Threshold { get; set; }
    }
}
