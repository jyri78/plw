<?php
// Settings for header and footer
$_html = _PLW_PG_SETTINGS['main']['t_html'];
$_title1 = _PLW_PG_SETTINGS['main']['title1'];
$_title2 = _PLW_PG_SETTINGS['main']['title2'];
$_body = _PLW_PG_SETTINGS['main']['t_body'];
$_hColor = _PLW_PG_SETTINGS['main']['hColor'];
$_hArgs = _PLW_PG_SETTINGS['main']['t_h1'];
$_hTitle = _PLW_PG_SETTINGS['main']['hTitle'];
$_hpArgs = _PLW_PG_SETTINGS['main']['t_p'];
$_hText = _PLW_PG_SETTINGS['main']['hText'];
$_footer_mw = _PLW_PG_SETTINGS['main']['footer_mw'];


(@include PATH_INC .'template/_header.inc') or die(ERROR_MSG);

foreach($g_subjects[0] as $c => $s):
?>

    <div class="w3-card-4 w3-<?= $s['colorTxt'] ?>">
        <header class="w3-panel w3-<?= $s['colorBack'] ?>">
            <h2><?= $s['title'] ?></h2>
        </header>

        <div class="w3-container">
            <div class="w3-bar-block w3-border w3-round-large">
                <a class="w3-bar-item w3-button w3-round-large w3-hover-shadow lecture" href="<?=
PATH_WEB .'?'. $c ?>"><?= APP_WORDS[APP_LANG]['preview'] ?></a>
                <div class="w3-margin-left w3-opacity w3-small" style="border-top:1px solid lightgray">

<?php
print_lectures($c, $s);
?>

                </div>
            </div>
        </div>

        <footer class="w3-panel w3-<?= $s['colorBack'] ?>">
            <h6><?= $s['footer'] ?></h6>
        </footer>
    </div>
<?php
endforeach;

if (sizeof($g_subjects[1])>0):
?>

    <div class="w3-container w3-padding"></div>
    <div class="w3-card-4 w3-opacity">
        <header class="w3-panel w3-<?= $_hColor ?> w3-<?= $g_theme[1]['h1']
?> w3-border-bottom" style="text-shadow:1px 1px 0 #444">
            <h3 class="lecture"><?= APP_WORDS[APP_LANG]['other'] ?></h3>
        </header>

        <div class="w3-panel">
            <p>
<?php
    foreach($g_subjects[1] as $f):
?>
                <a href="<?= PATH_WEB . $f .'/'
?>" class="w3-btn w3-round-large w3-<?= $g_theme[1]['btn'] ?> w3-border"><?= $f ?></a>
<?php
    endforeach;
?>
            </p>
        </div>
    </div>

<?php
endif;  //if (sizeof($g_subjects[1])>0):

(@include PATH_INC .'template/_footer.inc') or die(ERROR_MSG);
