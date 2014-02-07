namespace SaccubusCommons.Network

open System;
open System.IO;
open System.Net;
open System.Web;
open System.Text;
open System.Collections;
open SaccubusCommons.Functional;
open System.Xml;

module Xml =
    let parse str =
        try
            let doc = new XmlDocument();
            doc.LoadXml(str);
            Right doc.DocumentElement
        with
            | err -> Left err

