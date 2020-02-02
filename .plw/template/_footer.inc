

    <div class="w3-container"></div>
    <footer class="plw">
<?php
if ($g_inc == '_main.inc'):
?>
        <div class="w3-panel w3-round-large w3-<?= $g_theme[1]['header'] ?> w3-hover-shadow">
            <h6 style="border-bottom:1px solid gray">&copy; <?= INFO_NAME ?>, <?=
INFO_YEAR ?><?= date('Y')>INFO_YEAR ? '-'. date('Y') : '' ?></h6>

            <div class="w3-container w3-half w3-cell w3-mobile">
                <p class="w3-text-<?= $g_theme[1]['gray'] ?>-gray w3-small">
                    <b>PHP versioon:</b> <?= explode('-', phpversion())[0] ?>

                    <br><b>MySQL versioon:</b> <?= sql_ver_str() ?>

                    <br><b>Apache versioon:</b> <?= explode(' ', apache_get_version())[0] ?>

                </p>
            </div>
            <div class="w3-container w3-half w3-cell w3-mobile">
                <p class="w3-text-<?= $g_theme[1]['gray'] ?>-gray">
                    <b class="phone"></b>(<small class="ph1"></small>) <small class="ph2"></small>
                    <br><b class="email"></b><span class="addr1"></span><span class="addr2"></span><span class="addr3"></span>
                </p>
            </div>
        </div>

<?php
endif;  //$g_inc == '_main.inc'
?>
        <div class="w3-panel w3-margin-bottom plw">&nbsp;</div>
        <div class="w3-panel w3-round w3-light-gray w3-opacity w3-border w3-border-blue-gray" style="position:fixed;bottom:0;margin-bottom:0;z-index:3;width:100%<?=
$_footer_mw ?>">
            <div class="w3-container w3-small">
                <p class="w3-text-blue-gray w3-center plw">
                    Powered by <b><?= _PLW_NAME ?></b> &nbsp;<span class="w3-badge w3-<?= $g_theme[1]['span'] ?>"><?=
_PLW_VER ?></span> &nbsp; <a href="https://github.com/jyri78/plw" target="_blank">&#64;jyri78</a>
                </p>
            </div>
        </div>
    </footer>


</body>
</html>