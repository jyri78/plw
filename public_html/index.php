<?php
ini_set('display_errors', 1);
error_reporting(~E_ALL);  // remove '~', if something went wrong


//~ Change, if PLW folder in other place and you know what you do 🙂
define("PATH_INC", realpath("../.plw") .'/');




/* ---------------------------------------------------------------------
     DO NOT CHANGE!
   ---------------------------------------------------------------------
*/
$fldr = $_SERVER['PHP_SELF'];
if (substr($fldr, -1) != '/') {
    $fldr = substr($fldr, 0, strrpos($fldr, '/')+1);
}

//~ Some constants
define("PATH_MAIN", realpath("./") .'/');
define("PATH_WEB", $fldr);
define("ERROR_MSG", "OUCH! Program is kind a broken 🤔");

//~ Everything else is done in included files
(@include PATH_INC ."index.inc") or die(ERROR_MSG);
