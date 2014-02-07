module TestXML

open Microsoft.VisualStudio.TestTools.UnitTesting
open SaccubusCommons.Network
open SaccubusCommons.Functional

[<TestClass>]
type NetworkTest() =
    [<TestMethod>]
    member this.NormalXML() =
        let x = Xml.parse ("<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n<a></a>")
        match x with
            | Left err -> Assert.Inconclusive(err.Source + " / " + err.Message)
            | Right e -> Assert.IsTrue(e.Name.Equals "a")

    [<TestMethod>]
    member this.InvalidXML() =
        let x = Xml.parse ("<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n>")
        match x with
            | Left err -> ()
            | Right e -> Assert.Fail()
