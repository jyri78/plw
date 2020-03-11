<?php
/* =============================================================================
 * ~~ Functions ~~
 * =============================================================================
 * 
 * Main functions:
 *   get_theme()
 *   get_phone($subject)
 *   subject_settings($subject)
 *   subjects()
 *   get_subfolder($link) 
 * 
 * Used in '_footer.inc':
 *   sql_ver()
 *   sql_ver_str()
 * 
 * Used in '_main.inc' and '_subject.inc':
 *   lectures($subject)
 *   print_lectures($subject, $setting, $target = '')
 * 
 * Used in '_subject.inc':
 *   subject_links($subject)
 *   print_subject_links($subject)
 * 
 * Used in '_src.inc' and '_proj.inc':
 *   lecture_files($link)
 * 
 * Used in '_proj.inc':
 *   print_project_files()
 * 
 * Used in '_src.inc';
 *   print_lecture_files($subject, $lecture)
 *   highlight_source($file)
 */


// ---------------------------------------------------------------------
//~ Correct foldername
//~ (remove beginning "/" and add '/' to the end if necessary)
// ---------------------------------------------------------------------
function _fldr_name($name) {
    $nms = explode(';', $name);
    $ret = [];

    foreach ($nms as $nm) {
        $n = trim($nm);
        $l = strlen($n);

        if ($l > 3) {
            if (substr($n, 0, 1) != '/') {
                $n = '/'. $n;
                $l++;
            }
            if (substr($n, -1) == '/') $n = substr($n, 0, $l-1);

            $ret[] = $n;
        }
    }

    // If no folder exists, returns array with empty string
    return $ret;
}

// ---------------------------------------------------------------------
//~ Returns Main page theme colors
// ---------------------------------------------------------------------
function get_theme() {
    // Default settings
    $clrs = array(false, array(
        'body'   => 'light-green',
        'header' => 'lime',
        'h1'     => 'text-green',
        'span'   => 'amber',
        'btn'    => 'lime',
    ));
    $theme = array('light' => array('l4', 'l3'), 'dark' => array('d4', 'd5'));
    $link = PATH_INC .'css/w3-theme-'. APP_COLOR_THEME .'.css';

    // If Custom Theme is used
    if (APP_COLOR_THEME=='custom') {
        // If Custom Theme colors is set, than update link
        if (filesize(PATH_INC .'css/custom-theme.css')>999)
            $link = PATH_INC .'css/custom-theme.css';
        else
            return $clrs;
    }

    // If Color Theme CSS file exists, than use it's settings
    if (file_exists($link)) {
        $clrs[0] = $link;
        $clrs[1] = array('body'=>'theme-'. $theme[APP_THEME][0],
                         'header'=>'theme-'. $theme[APP_THEME][1],
                         'h1'=>'text-theme', 'span'=>'theme-d3',
                         'btn'=>'theme-'. $theme[APP_THEME][1],
                         'gray' => (APP_THEME == 'dark' ? 'light' : 'dark')
                        );
    }

    return $clrs;
}


// ---------------------------------------------------------------------
//~ Returns Phone Number
// ---------------------------------------------------------------------
function get_phone($subject) {
    $ph = str_split(INFO_PHONE);
    $r1 = '';
    $r2 = '';
    $cc = false;

    foreach ($ph as $chr) {
        switch ($chr) {
            case '(':
                $cc = true;
            break;
            case ')':
                $cc = false;
            break;
            case '+':  case '0':  case '1':  case '2':  case '3':
            case '4':  case '5':  case '6':  case '7':  case '8':
            case '9':
                if ($cc) $r1 .= _PLW_NUMBERS[$chr];
                else     $r2 .= _PLW_NUMBERS[$chr];
            break;
            default:
                if ($cc) $r1 .= $chr;
                else     $r2 .= $chr;
        }
    }
    if (!$r1)
        $r1 = _PLW_NUMBERS['+'] . _PLW_NUMBERS['3'] . _PLW_NUMBERS['7'] . _PLW_NUMBERS['2'];

    return array($r1, $r2);
}

// ---------------------------------------------------------------------
//~ Returns Subject settings
// ---------------------------------------------------------------------
function subject_settings($subject) {
    // Default values
    $ret = array(
        "title"  => '',  // mandatory
        "ctime"  => date("y-m-d"),
        "footer" => INFO_YEAR .'/'. (INFO_YEAR+1) .'õ.a &nbsp;(1. semester)',
        "colorTxt"  => 'pale-blue',
        "colorBack" => 'blue',
        "ignore"    => [],
    );

    // Get contents of Subjects '.settings' file
    $lines = file(PATH_MAIN . $subject .'/'. _PLW_FILES[0]
                 , FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);

    if ($lines) {
        // Read file contents line by line
        foreach ($lines as $line) {
            // Key-value pair is separated with symbol ':'
            $l = explode(':', $line);
            $c = count($l);

            // If no key-value pair, then go to next line
            if ($c < 2) continue;

            $ret[trim($l[0])] = trim($l[1]);

            // Allow one link in title and footer (append next part if necessary)
            if ($c>2 && ($l[0]=='title' || $l[0]=='footer') && substr($l[2], 0, 2)=='//')
                $ret[trim($l[0])] .= ':'. trim($l[2]);
        }
    }

    // Correct foldernames if necessary
    if($ret['ignore'])
        $ret['ignore'] = _fldr_name($ret['ignore']);

    return !$ret['title'] ? false : $ret;
}

// ---------------------------------------------------------------------
//~ Searches all Subject folders
// ---------------------------------------------------------------------
function subjects() {
    $ret = array();
    $tmp = array();
    $fldr = array();

    // Iterates all folders
    foreach (new DirectoryIterator(PATH_MAIN) as $f) {
        $fn = $f->getFileName();

        // Allow only folders and if there have settings files
        if ($f->isDot() || !$f->isDir()) continue;
        // If hidden folder not allowed, skip it
        if (substr($fn,0,1)=='.' && !SHOW_HIDDEN) continue;
        // Skip project folders (real name and name to show)
        if (in_array($fn, PROJECTS_FOLDER)) continue;
        // Skip, if required by user (file .hide)
        if (file_exists($fn .'/'. _PLW_FILES[4])) continue;

        $s = subject_settings($fn);

        if ($s===false) {
            if (SHOW_OTHER) $fldr[] = $fn;
        }
        else
            $tmp[$s['cdate'] .'__'. $fn] = $s;
    }
    sort($fldr);
    krsort($tmp);
    foreach ($tmp as $k => $v) $ret[explode('__', $k)[1]] = $v;

    return array($ret, $fldr);
}

// ---------------------------------------------------------------------
//~ Returns sources subfolder of Subjects lecture
// ---------------------------------------------------------------------
function get_subfolder($link) {
    $src = false;
    // Just in case check if ends with '/'
    if (substr($link, -1) == '/') $link = substr($link, 0, count($link)-1);

    // Check if is set subfolder
    // TODO: Accept several subfolders
    if (file_exists($link .'/'. _PLW_FILES[3])) {
        $src = _fldr_name(
                explode("\n", file_get_contents($link .'/'. _PLW_FILES[3]))[0]
            )[0] ?? '';

        // Check if folder exists
        if (!file_exists($link .'/'. $src)) $src = false;
    }

    return $src;
}


// ---------------------------------------------------------------------
//~ Finds SQL-server version
// ---------------------------------------------------------------------
function sql_ver() {
    $sql = "&lt;ERROR_CHECKING&gt;";
    $mysqli = new mysqli("localhost", SQL_USER, SQL_PWD);

    if (!mysqli_connect_errno()) {
        $sql = explode("-", $mysqli->server_info);
    }
    $mysqli->close();
    return $sql;
}

// ---------------------------------------------------------------------
//~ Returns SQL-server version as string
// ---------------------------------------------------------------------
function sql_ver_str() {
    $sql = sql_ver();
    return $sql[0] . (isset($sql[2]) && $sql[2]=="MariaDB"
                      ? "&nbsp; (<i>MariaDB&nbsp;". $sql[1] ."</i>&thinsp;)" : "");
}


// ---------------------------------------------------------------------
//~ Searches all lecture folders in subject
// ---------------------------------------------------------------------
function lectures($subject) {
    $ret = array();

    // Iterates all Subject's folders
    foreach (new DirectoryIterator($subject) as $f) {
        if($f->isDot() || !$f->isDir()) continue;
        // If hidden files/folders not allowed, continue in occurrence
        if (substr($f->getFileName(), 0, 1)=='.' && !SHOW_HIDDEN) continue;
        // If lecture folder contains file '.hide', then will ignore it as required
        if (file_exists($subject .'/'. $f .'/'. _PLW_FILES[4])) continue;

        $ret[] = $f->getFileName();
    }
    rsort($ret);
    return $ret;
}

// ---------------------------------------------------------------------
//~ Prints out Subject's lectures as links
// ---------------------------------------------------------------------
function print_lectures($subject, $setting, $target = '') {
    $link = '<a class="w3-bar-item w3-button w3-round-large w3-hover-shadow ';
    $lec = lectures(PATH_MAIN . $subject);

    foreach ($lec as $dir) {
        // Ignore folder set by settings
        if (in_array('/'. $dir, $setting['ignore'])) continue;

        // Reads date data, if is set
        $date = file_get_contents(PATH_MAIN . $subject .'/'. $dir .'/'. _PLW_FILES[2]);

        $sDate = $date ? ' <sup class="w3-text-'. $setting["colorBack"] .'">('
                . $date .')</sup>' : '';

        $src = get_subfolder(PATH_MAIN . $subject .'/'. $dir);

        // If sources page allowed and not in subject page,
        // then add two links (lecture folder and sources page)
        if ($src!==false && !$target):
?>
<?= $link ?>w3-border-right lecture lecture_s" href="<?=
        PATH_WEB . $subject .'/' . $dir ?>/"> <?= $dir . $sDate ?></a>
<?= $link ?>w3-border-left w3-center code" href="<?= PATH_WEB .'?src'
        . _PLW_REPLACES['SLS'] . str_replace(_PLW_REPLACES['SPC'][0], _PLW_REPLACES['SPC'][1],
                                             $subject . _PLW_REPLACES['SLS'] . $dir) ?>"></a>
<?php
        else:
?>
<?= $link ?>lecture" href="<?= PATH_WEB . str_replace(_PLW_REPLACES['SPC'][0], _PLW_REPLACES['SPC'][1]
        , $subject .'/' . $dir) ?>/"<?= $target ?>> <?= $dir . $sDate ?></a>
<?php
        endif;
    }

    if ($target) {
        return $lec[sizeof($lec)-1];
    }
}


// ---------------------------------------------------------------------
//~ Returns Subject links
// ---------------------------------------------------------------------
function subject_links($subject) {
    $ret = array();

    // Get contents of Subjects '.links' file
    $lines = file(PATH_MAIN . $subject .'/'. _PLW_FILES[1]
            , FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);

    if ($lines) {
        // Read file contents line by line
        foreach ($lines as $line) {
            // If line separator
            if (substr(trim($line), 0, 2) == '--') {
                $ret[] = array();
                continue;
            }

            // Link-title pair is separated with symbol ';'
            $l = explode(';', $line);
            if (sizeof($l) < 2) continue;  // ignore other variants
            $ret[] = array(trim($l[0]), trim($l[1]));
        }
    }
    return $ret;
}

// ---------------------------------------------------------------------
//~ Prints out Subject's links
// ---------------------------------------------------------------------
function print_subject_links($subject) {
    $bAnchor = '<a class="w3-bar-item w3-button w3-round-large w3-hover-shadow" href="';
    $links = subject_links($subject);

    foreach ($links as $link) {
        if (!sizeof($link)):
            echo "<hr>\n";
        else: ?>
<?= $bAnchor . $link[0] ?>" target="_blank">&#x1F517;&nbsp; <?= $link[1] ?></a>
<?php
        endif;
    }
}


// ---------------------------------------------------------------------
//~ Returns Lectures PHP source files
// ---------------------------------------------------------------------
function lecture_files($link, $proj = FALSE) {
    $ret = array();

    // Iterates recursively Lecture folder and subfolders
    foreach (new DirectoryIterator($link) as $f) {
        $fn = $f->getFileName();

        // Don't show system setting files
        if ($f->isDot() || in_array($fn, _PLW_FILES)) continue;

        // Don't show Word Press files
        if (substr($fn, 0, 3) == 'wp-') continue;

        // Depending on settings, ignores hidden files or not
        if (!SHOW_HIDDEN && substr($fn,0,1)=='.') continue;

        if ($f->isDir() && !$proj) {
            $a = lecture_files($link .'/'. $fn);
            if(sizeof($a) > 0) $ret['d_'. $fn] = $a;
        }
        else {
            if (in_array(pathinfo($fn, PATHINFO_EXTENSION), SRC_EXT)) $ret['f_'. $fn] = $fn;
        }
    }
    ksort($ret);
    return $ret;
}


// ---------------------------------------------------------------------
//~ Prints out Project files (PHP)
// ---------------------------------------------------------------------
function print_project_files() {
    global $g_proj;
    $link1 = '<a class="w3-bar-item w3-button w3-round-large w3-hover-shadow';
    $link2 = ' src" href="';

    // Ignore subdirectories (can be used for includes in php file)
    $files = lecture_files(PATH_MAIN . PROJECTS_FOLDER[0], true);

    foreach ($files as $file) {
        $f = substr($file, 0, -4);

        echo $link1 . ($f == $g_proj
            ? ' w3-light-gray w3-border w3-border-light-grey w3-hover-border-blue-grey'
            : '') . $link2 . PATH_WEB .'?'. PROJECTS_FOLDER[1] .'='. $f .'">'
            . $f .'</a>'. "\n";
    }
}


// ---------------------------------------------------------------------
//~ Prints out Lecture files
// ---------------------------------------------------------------------
function print_lecture_files($subject, $lecture) {
    $link = PATH_MAIN . $subject .'/'. $lecture;
    $src = get_subfolder($link);

    // Disable erroneous folder
    if ($src===false) return;
    _print_files(lecture_files($link . $src));
}

// Helper function for recursive printing
function _print_files($files, $src = '', $hlp = '') {
    global $g_src, $g_subfldr;
    $link1 = '<a class="w3-bar-item w3-button w3-round-large w3-hover-shadow';
    $link2 = ' src" href="';

    foreach ($files as $file => $fldr) {
        if (substr($file, 0, 2) == 'd_'):
            $f = substr($file, 2);
?>
<div class="w3-margin-left w3-margin-bottom w3-leftbar w3-border-bottom w3-round w3-padding-small">
<span class="lecture lecture_f"> <?= $f ?></span>
<?php
_print_files($fldr, $src . $f . _PLW_REPLACES['DS'][1], $hlp . $f .'/');
?>
</div>
<?php
        else:
?>
<?= $link1 . ($g_src == SUBJECT .'/'. LECTURE . $g_subfldr .'/'. $hlp . $fldr
        ? ' w3-light-gray w3-border w3-border-light-grey w3-hover-border-blue-grey' : '')
        . $link2 . PATH_WEB .'?src'. _PLW_REPLACES['SLS']
        . str_replace(_PLW_REPLACES['SPC'][0], _PLW_REPLACES['SPC'][1],
                      SUBJECT . _PLW_REPLACES['SLS'] . LECTURE . _PLW_REPLACES['LFS']
                      . str_replace(_PLW_REPLACES['DOT'][0], _PLW_REPLACES['DOT'][1], $src . $fldr))
        ?>"> <?= $fldr ?></a>
<?php
        endif;
    }
}

// ---------------------------------------------------------------------
//~ Highlights Lecture source file with line numbers;
//~ idea from: https://www.php.net/manual/en/function.highlight-file.php
// ---------------------------------------------------------------------
function highlight_source($file) {
    // TODO: highlight sources of different languages (besides PHP)

    //Strip code and first span
    $src = _highlight_file2($file, true);
    $code = substr($src[1], 36, -12);
    //Split lines
    $lines = explode('<br />', $code);
    //Count
    $lineCount = count($lines);
    //Calc pad length
    $padLength = strlen($lineCount);
    
    //Loop lines
    $out = '';
    foreach($lines as $i => $line) {
        //Create line number
        $lineNumber = str_pad($i + 1,  $padLength, '0', STR_PAD_LEFT);
        //Print line
        $out .= sprintf('<br><span class="num">%s</span><span>%s</span>', $lineNumber, $line);
    }

    //Re-Print the code and span again
    echo $src[0] .'<code><span style="color:#000">'. substr($out, 4) .'</span></code>';
}
// Rewrite for PHP highlight_file()
function _highlight_file2($fl,$ret){
    if(!isset($ret)) $ret = false;
    $str = highlight_file($fl, true);
    preg_match_all("/\<span style=\"color: #([\d|A|B|C|D|E|F]{6})\"\>.*?\<\/span\>/", $str, $mtch);
    $m = array_unique($mtch[1]);

    $cls = '<style scoped>';
    $rpl = array("</a>");
    $mtc = array("</span>");
    $i = 0;
    foreach($m as $clr) {
        $cls .= 'a.c'. $i .'{color:#'. $clr .'}';
        $rpl[] = '<a class="c'. $i++ .'">';
        $mtc[] = '<span style="color: #'. $clr. '">';
    }
    $cls .= '</style>';
    $str2 = str_replace($mtc, $rpl, $str);
    if($ret) return array($cls, $str2);
    else echo '<style scoped>' . $cls . $str2;
}
