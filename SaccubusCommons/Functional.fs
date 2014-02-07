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
    let (|>) = (>>=)
