<?php
// Settings for header and footer
$_html = _PLW_PG_SETTINGS['src']['t_html'];
$_title1 = $g_subjects[0][SUBJECT]["title"];
$_title2 = _PLW_PG_SETTINGS['src']['title2'];
$_body = _PLW_PG_SETTINGS['src']['t_body'];
$_hColor = $g_subjects[0][SUBJECT]["colorBack"];
$_hArgs = _PLW_PG_SETTINGS['src']['t_h1'];

$_hTitle = $g_subjects[0][SUBJECT]['title']
        .' &nbsp;<span class="w3-large w3-opacity w3-border w3-round-large w3-disabled source">&nbsp;'
        . APP_WORDS[APP_LANG]['source'] .'&nbsp;</span>';

$_hpArgs = _PLW_PG_SETTINGS['src']['t_p'];
$_hText = _PLW_PG_SETTINGS['src']['hText'];
$_footer_mw = _PLW_PG_SETTINGS['src']['footer_mw'];


(@include PATH_INC .'template/_header.inc') or die(ERROR_MSG);
?>

    <div class="w3-sidebar w3-bar-block w3-border" style="width:35%;height:72%">
        <div class="w3-container">
            <a class="w3-bar-item w3-button w3-round-large w3-hover-shadow" href="<?=
PATH_WEB ?>">&#x1F519;&nbsp; <?= APP_WORDS[APP_LANG]['back'] ?></a>
            <div class="w3-margin-left w3-margin-top w3-leftbar w3-round w3-padding-small" style="border-top:1px solid lightgray">
                <p class="w3-margin-bottom code_s"> &nbsp;<?= LECTURE ?><?=
($g_subfldr ? ' <sup>'. $g_subfldr .'/</sup>' : '') ?></p>

<?php
print_lecture_files(SUBJECT, LECTURE);
?>

            </div>
        </div>
    </div>

    <div class="w3-container w3-margin-bottom w3-margin-right w3-padding-large w3-border w3-round w3-pale-blue" style="margin-left:35%;width:65%;min-height:80vh">

<?php
if ($g_src)
    highlight_source(PATH_MAIN . $g_src);
else
    echo '<b>'. APP_WORDS[APP_LANG]['select_file'] .'</b>';
?>


    </div>
<?php
(@include PATH_INC .'template/_footer.inc') or die(ERROR_MSG);
