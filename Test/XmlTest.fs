module Test

open Microsoft.VisualStudio.TestTools.UnitTesting
open SaccubusCommons.Network
open SaccubusCommons.Functional

[<TestClass>]
type NetworkTest() =
    [<TestMethod>]
    member this.TestGPLString() =
        let x = Http.getString "http://www.gnu.org/licenses/gpl.txt" "utf-8"
        match x with
            | Right x -> Assert.IsTrue(x.Length > 0)
            | Left y -> Assert.Fail()

    [<TestMethod>]
    member this.TestGPLBytes() =
        let x = Http.getBytes "http://www.gnu.org/licenses/gpl.txt"
        match x with
            | Right x -> Assert.IsTrue(x.Length > 0)
            | Left y -> Assert.Fail();
