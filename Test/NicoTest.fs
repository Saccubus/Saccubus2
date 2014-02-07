module TestNico

open Microsoft.VisualStudio.TestTools.UnitTesting
open SaccubusCommons.Network
open SaccubusCommons.Functional
open SaccubusCommons.Niconico

[<TestClass>]
type NetworkTest() =
    [<TestMethod>]
    member this.TestLogin() =
        login (Own ("saccubus@gmail.com","test1234")) (
                fun r ->
                    match r with
                        | Right x -> ()
                        | Left x -> Assert.Fail(x.Message)
            ) |> Async.RunSynchronously
    [<TestMethod>]
    member this.TestLoginFail() =
        login (Own ("saccubus@gmail.com","test1234!")) (
                fun r ->
                    match r with
                    | Right x -> Assert.Fail("失敗しないとおかしい")
                    | Left x -> ();
            ) |> Async.RunSynchronously
    [<TestMethod>]
    member this.TestGetMetaInfo() =
        fetchMetaInfo "sm60" (
            fun r ->
                match r with
                    | Right x -> Assert.AreEqual(x.title, "なに勘違いしているんだ") |> ignore
                    | Left x -> Assert.Fail(x.Message)
        ) |> Async.RunSynchronously
        fetchMetaInfo "sm61" (
            fun r ->
                match r with
                    | Right x -> Assert.Fail("失敗しないとおかしい")
                    | Left x -> ()
        ) |> Async.RunSynchronously
