namespace SaccubusCommons
open SaccubusCommons.Functional

module Niconico =
    type Login =
        | Own of (string * string)
        | Chrome
        | Firefox
        | InternetExplorer
    type LoginContext = {
        cookie : string
    };

    let login (login:Login) : Either<System.Exception, LoginContext> =
        
        Right { cookie = "" };
