namespace SaccubusCommons

module Functional =
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
    type EitherBuilder() =
        member x.Bind(comp : Either<'e, 'a>, func : ('a -> Either<'e, 'b>)) = comp >>= func
        member x.Return(value:'a) : Either<'e, 'a> = Right value
        member x.ReturnFrom(value : Either<'e, 'a>) : Either<'e, 'a> = value
    let either = new EitherBuilder()
