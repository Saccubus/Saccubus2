module Functional
    type Either<'E, 'A> =
    | Left  of 'E
    | Right of 'A
    let (>>=) (x:Either<'E, 'A>) (f : ('A -> Either<'E, 'B>)) =
        match x with
            | Left x -> Left x
            | Right y -> f y
    let ret = Right
    let (>>) (x:Either<'E, 'A>) (y:Either<'E, 'A>)=
        match x with
            | Left x -> Left x
            | Right _ -> y
    let (|>) = (>>=)
    let div x y =
        match y with
         | 0 -> Left "Divided by ZERO"
         | _ -> Right (x / y)
    let r = ret 10 
          |> fun x -> div x 100
//          |> div 10
          |> fun x -> ret (string x)
    let p = match r with
            | Right x -> x
            | Left y -> y;
    System.Console.WriteLine(p)

