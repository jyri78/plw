<?php
// Settings for header and footer
$_html = _PLW_PG_SETTINGS['proj']['t_html'];
$_title1 = _PLW_PG_SETTINGS['proj']['title1'];
$_title2 = _PLW_PG_SETTINGS['proj']['title2'];
$_body = _PLW_PG_SETTINGS['proj']['t_body'];
$_hColor = _PLW_PG_SETTINGS['proj']['hColor'];
$_hArgs = _PLW_PG_SETTINGS['proj']['t_h1'];
$_hTitle = _PLW_PG_SETTINGS['proj']['hTitle'];
$_hpArgs = _PLW_PG_SETTINGS['proj']['t_p'];
$_hText = _PLW_PG_SETTINGS['proj']['hText'];
$_footer_mw = _PLW_PG_SETTINGS['proj']['footer_mw'];


(@include PATH_INC .'template/_header.inc') or die(ERROR_MSG);
?>

    <div class="w3-sidebar w3-bar-block w3-border" style="width:29%;height:72%">
        <div class="w3-container">
            <a class="w3-bar-item w3-button w3-round-large w3-hover-shadow" href="<?=
PATH_WEB ?>">&#x1F519;&nbsp; <?= APP_WORDS[APP_LANG]['back'] ?></a>
            <div class="w3-margin-left w3-margin-top w3-leftbar w3-round w3-padding-small" style="border-top:1px solid lightgray">
                <!-- p class="w3-margin-bottom code_s"> &nbsp;</p -->

<?php
print_project_files();
?>

            </div>
        </div>
    </div>

    <div class="w3-container w3-margin-bottom w3-margin-right w3-padding-large w3-border w3-round w3-pale-blue" style="margin-left:29%;width:71%;min-height:20vh">

<?php
$inc = PATH_MAIN . PROJECTS_FOLDER[0] .'/'. $g_proj .'.php';

if ($g_proj && file_exists($inc))  // just in case
    include $inc;
else
    echo '<b>'. APP_WORDS[APP_LANG]['select_file'] .'</b>';
?>


    </div>
<?php
(@include PATH_INC .'template/_footer.inc') or die(ERROR_MSG);
