<?php
// Settings for header and footer
$_html = _PLW_PG_SETTINGS['subject']['t_html'];
$_title1 = $g_subjects[0][SUBJECT]["title"];
$_title2 = _PLW_PG_SETTINGS['subject']['title2'];
$_body = _PLW_PG_SETTINGS['subject']['t_body'];
$_hColor = $g_subjects[0][SUBJECT]["colorBack"];
$_hArgs = _PLW_PG_SETTINGS['subject']['t_h1'];
$_hTitle = $g_subjects[0][SUBJECT]["title"];
$_hpArgs = _PLW_PG_SETTINGS['subject']['t_p'];
$_hText = _PLW_PG_SETTINGS['subject']['hText'];
$_footer_mw = _PLW_PG_SETTINGS['subject']['footer_mw'];


(@include PATH_INC .'template/_header.inc') or die(ERROR_MSG);
?>

    <div class="w3-sidebar w3-bar-block" style="width:25%;height:80%">
        <div class="w3-container">
            <a class="w3-bar-item w3-button w3-round-large w3-hover-shadow" href="<?=
PATH_WEB ?>">&#x1F519;&nbsp; <?= APP_WORDS[APP_LANG]['back'] ?></a>
            <div class="w3-margin-left w3-margin-top" style="border-top:1px solid lightgray">

<?php
$lect = print_lectures(SUBJECT, $g_subjects[0][SUBJECT], ' target="lectures"');
?>

            </div>
        </div>
        <hr>
        <div class="w3-container w3-small w3-opacity">

<?php
print_subject_links(SUBJECT);
?>

        </div>

    </div>
    <iframe src="<?= ($lect ? PATH_WEB . SUBJECT .'/'. $lect .'/'
:'') ?>" name="lectures" id="lectures" class="w3-border w3-round" style="margin-left:25%;width:75%;height:80%"></iframe>
<?php
(@include PATH_INC .'template/_footer.inc') or die(ERROR_MSG);
