using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Biomed_Closed_Loop_GUI
{
    public static class PulseParameters
    {
        //public static readonly Dictionary<int, ulong> blankDurations = new Dictionary<int, ulong>
        //{
        //    // ROUND(1_000_000 / FREQ) - 80 - 80
        //    // I mean, this could be a function but for the proof of concept I want to specify the values myself
        //    { 150, 6506 },
        //    { 130, 7532 },
        //    { 110, 8930 },
        //    { 90, 10951 },
        //    { 70, 14125 },
        //    { 50, 19840 },
        //};
        public static ulong blankDuration(int frequency, ulong positivePulseDuration = 80, ulong negativePulseDuration = 80)
        {
            ulong blankDuration = (ulong)Math.Round(1e6 / frequency, 0) - positivePulseDuration - negativePulseDuration;

            return blankDuration;
        }

        public static readonly int defaultFrequency = 130;
    }
}
