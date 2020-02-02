<?php
/* --  MANDATORY --
*/
define("INFO_NAME", '');           // Your name
define("INFO_COLLEGE", '');        // College name
define("INFO_COURSE", '');         // name of course
define("INFO_YEAR", 0);            // year of admission
define("INFO_PHONE", '');          // default country code: (+372)
define("INFO_EMAIL", '');          // e-mail to show
define("INFO_REQUEST_VALUE", '');  // used in '/?_info=<value>' for extra security
/* 
End of MANDATORY part
*/


// Main page Color Theme
define("APP_COLOR_THEME", '');  // 'custom' or color name (between 'w3-theme-' and '.css')
define("APP_THEME", '');        // 'dark' or 'light'

// Additional color library names used in subjects .settings file, if Color Material not enough;
// read more about libraries in https://www.w3schools.com/w3css/w3css_color_libraries.asp
define("APP_COLOR_LIBS", array());  // use only name(s) between 'w3-colors-' and '.css'


// Think carefully before changing!
define("SRC_EXT", array('php', 'inc'));
define("SHOW_HIDDEN", false);  // hidden are files/folders beginning with dot
define("SHOW_OTHER", false);   // all other folders not containing .settings file


// Language settings
define("APP_LANG", 'et');   // at the moment "en" or "et"

// Some words used in App (You can add other languages and use it)
define("APP_WORDS", array(
    "en" => array(
        "preview"      => 'Preview',
        "other"        => 'Other folders',
        "back"         => 'Back',
        "source"       => 'Source',
        "select_file"  => "Select file to see it's source",
    ),
    "et" => array(
        "preview"      => 'Eelvaade',
        "other"        => 'Teised kaustad',
        "back"         => 'Back',
        "source"       => 'lähtekood',
        "select_file"  => 'Vali fail, mida kuvada',
    )
));




//----------------------------------------------------------------------
//~ DO NOT CHANGE!
//----------------------------------------------------------------------
define("SETTINGS", array(
    "INFO_NAME" => INFO_NAME,
    "INFO_COLLEGE" => INFO_COLLEGE,
    "INFO_COURSE" => INFO_COURSE,
    "INFO_YEAR" => INFO_YEAR,
    "INFO_PHONE" => INFO_PHONE,
    "INFO_EMAIL" => INFO_EMAIL,
    "INFO_REQUEST_VALUE" => INFO_REQUEST_VALUE,
));
