<?php
// Important includes
(@include PATH_INC .".settings.php") or die(ERROR_MSG);

// Checking required settings
foreach (SETTINGS as $k => $v)
    if (!$v)
        die("SETTINGS not set yet 🤔");

// Projects POST (doesn't need any functions included below)
if (isset($_GET[PROJECTS_FOLDER[1]]) && !empty($_GET[PROJECTS_FOLDER[1]]) && !empty($_POST)) {
    $p = filter_input(INPUT_GET, PROJECTS_FOLDER[1], FILTER_SANITIZE_STRING, FILTER_FLAG_STRIP_LOW);
    $f = PATH_MAIN . PROJECTS_FOLDER[0] .'/'. $p .'.php';
    if (file_exists($f)) {
        include $f;
        exit;
    } else {
        header("Location:". PATH_WEB);  // disallow unknown projects
    }
}

(@include PATH_INC ."functions.php") or die(ERROR_MSG);


// ---------------------------------------------------------------------
//~ In-App settings, do not change
// ---------------------------------------------------------------------
define("_PLW_NAME", 'Programming Lectures Web');
define("_PLW_VER", '1.1');


define("_PLW_NUMBERS", array("+" => '➕',
    "0" => '0️⃣', "1" => '1️⃣', "2" => '2️⃣', "3" => '3️⃣', "4" => '4️⃣',
    "5" => '5️⃣', "6" => '6️⃣', "7" => '7️⃣', "8" => '8️⃣', "9" => '9️⃣',
));

define("_PLW_FILES", array(
    '.settings', '.links', '.date', '.src', '.hide',  // do not change order!
    '.settings.php',
));

define("_PLW_REPLACES", array(
    'SLS' => '--',  // subject-lecture separator
    'LFS' => '__',  // lecture-file separator

    'DS'  => array('/', '--'),  // directory separator and replacement
    'DOT' => array('.', '~'),   // dot and replacement (some browsers tend to replace with underscore)
    'SPC' => array(' ', '~~'),   // space and replacement
));


$g_theme = get_theme();  // Color Theme of main page

define("_PLW_PG_SETTINGS", array(
    'main' => array(
        't_html'    => '',
        'title1'    => INFO_NAME,
        'title2'    => INFO_COURSE,
        't_body'    => ' class="w3-'. $g_theme[1]['body'] .'" style="max-width:800px;margin:auto"',
        'hColor'    => $g_theme[1]['header'],
        't_h1'      => ' class="w3-'. $g_theme[1]['h1'] .'" style="text-shadow:1px 1px 0 #444"',
        'hTitle'    => INFO_NAME .' – '. INFO_COURSE,
        't_p'       => 'class="w3-text-'. $g_theme[1]['gray'] .'-gray" style="border-top:1px solid gray"',
        'hText'     => INFO_COLLEGE,
        'footer_mw' => ';max-width:800px',
    ),
    'proj' => array(
        't_html'    => '',
        'title1'    => APP_WORDS[APP_LANG]['projects'],
        'title2'    => INFO_NAME,
        't_body'    => ' class="w3-'. $g_theme[1]['body'] .'"',
        'hColor'    => $g_theme[1]['header'],
        't_h1'      => ' class="w3-'. $g_theme[1]['h1'] .'" style="text-shadow:1px 1px 0 #444"',
        'hTitle'    => APP_WORDS[APP_LANG]['projects'],
        't_p'       => 'class="w3-text-'. $g_theme[1]['gray'] .'-gray" style="border-top:1px solid gray"',
        'hText'     => INFO_NAME .' – '. INFO_COURSE,
        'footer_mw' => '',
    ),
    'subject' => array(
        't_html'    => ' style="height:100%"',
        //'title1'
        'title2'    => INFO_NAME,
        't_body'    => ' style="height:100%"',
        //'hColor'
        't_h1'      => '',
        //'hTitle'
        't_p'       => 'class="w3-text-light-gray"',
        'hText'     => INFO_NAME .' – '. INFO_COURSE,
        'footer_mw' => '',
    ),
    'src' => array(
        't_html'    => ' style="height:100%"',
        //'title1'
        'title2'    => INFO_NAME,
        't_body'    => ' style="height:100%"',
        //'hColor'
        't_h1'      => '',
        //'hTitle'
        't_p'       => 'class="w3-text-light-gray"',
        'hText'     => INFO_NAME .' – '. INFO_COURSE,
        'footer_mw' => '',
    ),
));


// ---------------------------------------------------------------------
//~ JavaScript
// ---------------------------------------------------------------------
if (isset($_GET["js"])) {
    header("Content-type: text/javascript");
    echo file_get_contents(PATH_INC . 'js/w3.min.js');
    echo "\n\n";
    echo file_get_contents(PATH_INC . 'js/plw.min.js');

    // Include also projects JavaScript (same name in folder 'js')
    if (isset($_GET[PROJECTS_FOLDER[1]])) {
        $p = filter_input(INPUT_GET, PROJECTS_FOLDER[1], FILTER_SANITIZE_STRING, FILTER_FLAG_STRIP_LOW);
        $js = PATH_MAIN . PROJECTS_FOLDER[0] .'/js/'. $p .'.js';

        if (file_exists($js)) {
            echo "\n\n/* Project: ". $p .".php */\n";
            echo file_get_contents($js);
        }
    }
    exit;
}


// ---------------------------------------------------------------------
//~ CSS content
// ---------------------------------------------------------------------
if (isset($_GET["css"])) {
    $ph = get_phone();
    $m = explode('@', INFO_EMAIL);

    header("Content-type: text/css");
    echo file_get_contents(PATH_INC . 'w3.css');

    foreach(APP_COLOR_LIBS as $clr)
        echo @file_get_contents(PATH_INC . 'css/w3-colors-'. $clr .'.css');

    echo file_get_contents($g_theme[0]);
?>


/* <?= _PLW_NAME ?> styles */
.plw,.lecture,.code,.code_s,.num,.source{-webkit-user-select:none;-moz-user-select:none;-ms-user-select:none;user-select:none}
.plw,.lecture_f,.code_s,.num{cursor:default}.code_s>sup{font-weight:normal;color:rgba(0,0,0,.5)}
.lecture:before{content:"📁 "}.code:before,.code_s:before{font-weight:bold;content:"</>"}.src:before{content:"📝 "}
.w3-container .lecture_s,.w3-container .code{display:inline-block}.w3-container .lecture_s{width:80%}.w3-container .code{width:18%}
.code_s{font-weight:bold}.phone,.email{margin-right:10px}.phone:before{content:"☎︎"}.email:before{content:"✉︎"}
.addr1:before{content:"<?= $m[0] ?>"}.ph1:before{content:"<?= $ph[0] ?>"}.addr2:before{content:"@"}.ph2:before{content:"<?= $ph[1] ?>"}.addr3:before{content:"<?= $m[1] ?>"}
.num{background-color:#f6f6fc;color:#999;margin-right:1em}.num:after{content:" :";font-weight:bold}
<?php
    exit;
}

// ---------------------------------------------------------------------
//~ PHPInfo content
// ---------------------------------------------------------------------
if (isset($_GET["_info"]) && $_GET["_info"] == INFO_REQUEST_VALUE) {
    header("Content-type: text/html");
    echo phpinfo();
    exit;
}




/* =============================================================================
 * ~~ Page selection ~~
 * =============================================================================
 */

// Global variables
$g_inc = '_main.inc';
$g_src = '';
$g_subjects = subjects();
$g_subfldr = '';


// Accept only one request key
if (sizeof($_GET) > 1) {
    header('Location: '.  PATH_WEB);

    // If by some reason header won't work
    echo 'Too many QUERY strings 😓';
    exit;
}
if (sizeof($_GET) == 1) {
    $k = str_replace(_PLW_REPLACES['SPC'][1], _PLW_REPLACES['SPC'][0], array_keys($_GET)[0]);

    if ($k == PROJECTS_FOLDER[1]) {
        $g_inc = '_proj.inc';
        $g_proj = filter_input(INPUT_GET, $k, FILTER_SANITIZE_STRING, FILTER_FLAG_STRIP_LOW);

        // If poject file does not exist, reload page
        if ($g_proj && !file_exists(PATH_MAIN . PROJECTS_FOLDER[0] .'/'. $g_proj .'.php')) {
            header("Location:". PATH_WEB .'?'. PROJECTS_FOLDER[1]);
            exit();
        }

        define("SUBJECT", '');  // for project page design (header)
    }
    else {
        $__s = '';

        foreach ($g_subjects[0] as $subj => $s) {
            // If Subject folder is requested ...
            if (isset($_GET[str_replace(_PLW_REPLACES['SPC'][0], _PLW_REPLACES['SPC'][1], $subj)])) {
                $g_inc = '_subject.inc';
                $__s = $subj;
                break;
            }
            // ... or preview of source files
            elseif (strpos($k, 'src'. _PLW_REPLACES['SLS'] . $subj) !== false) {
                $t = explode(_PLW_REPLACES['LFS'], $k);
                $l = explode(_PLW_REPLACES['SLS'], $t[0]);

                // Allow to preview only allowed Lecture files
                if (file_exists(PATH_MAIN . $subj .'/'. $l[2] .'/'. _PLW_FILES[3])) {
                    $g_inc = '_src.inc';
                    $g_subfldr = get_subfolder($l[1] .'/'. $l[2]);  // TODO: Accept several subfolders

                    // If source file is selected
                    if (sizeof($t) > 1) {
                        $g_src = $l[1] .'/'. $l[2] . $g_subfldr .'/' . str_replace(
                                _PLW_REPLACES['DOT'][1], _PLW_REPLACES['DOT'][0]
                                , str_replace(_PLW_REPLACES['DS'][1], _PLW_REPLACES['DS'][0], $t[1])
                            );
                    }

                    $__s = $subj;
                    define("LECTURE", $l[2]);
                    break;
                }
            }
        }

        // If no valid page, then reload
        if (!$__s) {
            header('Location: '.  PATH_WEB);

            // If by some reason header won't work
            echo 'Unknown QUERY "'. $k .'"... 🤔';
            exit;
        }

        define("SUBJECT", $__s);
        unset($__s);
    }
}




/* =============================================================================
 * ~~ Page include ~~
 * =============================================================================
 */

header("Content-type: text/html");
(@include PATH_INC .'template/'. $g_inc) or die(ERROR_MSG);
