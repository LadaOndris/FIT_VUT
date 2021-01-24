/************************************************************
 *      ROZSIVAL MICHAL                                     *
 *      IVS - project 2                                     *
 *      FEB/MAR 2019                                        *
 *      Interface for MathLibrary's testing classes         *
 *      Version 1.0                                         *
 ************************************************************/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MathLibraryTests
{
    /// <summary>
    /// Auxiliari interface for SineExpTest, CosineExpTest and TangentExpTest classes
    /// </summary>
    interface ITestTrigono
    {
        void InputZero();

        void InputPiDivSix();

        void InputPiDivFour();

        void InputTwoPiDivSix();

        void InputPiDivTwo();

        void InputFourPiDivSix();

        void InputThreePiDivFour();

        void InputFivePiDivSix();

        void InputPi();

        void InputSevenPiDivSix();

        void InputFivePiDivFour();

        void InputEightPiDivSix();

        void InputThreePiDivTwo();

        void InputTenPiDivSix();

        void InputSevenPiDivFour();

        void InputElevenPiDivSix();

        void RandomValues();

    }
}
