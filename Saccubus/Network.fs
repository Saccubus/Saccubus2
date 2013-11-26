namespace Saccubus.Network

open System
open System.IO;
open System.Net;
open System.Web;
open System.Text;
open System.Collections;
open Functional

module Http =
    let getBytes (url:string) : Either<Exception, byte[]> = 
        let cl = new System.Net.WebClient();
        Right (cl.DownloadData(url))

    let getString (url:string) (enc:string) : Either<Exception, string> = 
        let enc = System.Text.Encoding.GetEncoding(enc)
        let cl = new System.Net.WebClient();
        let st = cl.OpenRead(url)
        let sr = new System.IO.StreamReader(st, enc)
        try
            Right ( sr.ReadToEnd() )
        finally
            sr.Close()
            st.Close()
    
    let getAsyncString (url:string) (enc:string) (cont:Either<Exception, string> -> 'a) =
        cont (getString url enc);

    let getAsyncBytes (url:string) (enc:string) (cont:Either<Exception, byte[]> -> 'a) =
        cont (getBytes url);

    let postBytes (url:string) (hash:Hashtable) = 
        null

module Html =
    let e = 1

module Xml =
    let e = 1
