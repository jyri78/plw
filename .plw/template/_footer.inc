

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
                    Powered by <img style="margin:-5px 5px"
src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAC0AAAAYCAMAAABZc4S2AAAABGdBTUEAALGPC/xhBQAAAAFzUkdCAK7OHOkAAAGAUExURUdwTOTXxti+o9vJt9rKuci4r7yqpNvQysy6rtjNxtrMvMGwquXh39HDusqmhNrLvs6+tevfzNXEs+rezb2yss6zmaWSkbimnM2yntnHsa6Qg7CHbqijqdvAoOjdz9vHrs29trObk6uWi7uUgnxqY41yYNe4lcSjieXczdnMwKiPhMuuo+nPrKyIbpd0XsSCU76cf9u5lsKiiMuIWLt/WNi9oJ1XL6JdNt/CoMehfcuwl7iRepZvVnE7INGUZ3JMOOPKrOHHpKR8YnpCJbZwRNuaalg8L5ZbOZF2aH1ZRcWLYsCXda+Rd45KKF8wHGxIN/Xhxb56TXlSP15HPYlQNcurjLichdOvitzFq6mBY+vXu66RhkUlGpNTLHRbVIxpU61wSoRqYLuSbaxmPItgSeCic6JiP6FzVfPcvJNoTe7Xtdi0ioRFImU8K7SJZYxiUrV7XsR5RL+LcrSDcp59arqontKyktO+q4JiUL+vpJqFgcGoklMoGNO3nMqRadqSWmvWEQsAAAB6dFJOUwBtw75LqccKHycTdwM1+l2KfhjHiI7i6PLXp/Tg3PqWQbpo5uzq162++sjM///////////////////////////////////////////////////////////////////////////////////////////////////////+Hf3caQAAArJJREFUOMuFk2dT4lAUhukISBG7Y3f7phFCC4mB0HuRjvQO0sGu+9f3KsMOi46+H+7c8twzp3I4rxIrhb937kTCDTnnc8nOzObxCB+Ns9lt2erH7OrJaDAYEN4IMWhU+27Ryhti4UYsGmtRFNWikWK97opVS1vL+ApP/cKt8cCqGleGw+EfhxYdVgx6VyyaX8KluyAaMXddAPaSbL9uJ1BHzaGN2PUuQ8AWyu+LF2Axn8vhKNfXXu9ULJwmRt5arQZoe92Qs3W7pY2FqPi7HMmPdcnsJJrel6jn55rD4dBqIwa9/ooOOu8lc1jCTwm4h2vz0xRBqNuW99zrOD9H7fqA/soWfLzYn70qedfxm5+H3Pnf4wkCY3C/Sni9L7QhEMjZgpeXX2Z2rRqT4umG/8+tPQSG8YSfahEEoEFScjka0F9lcsGRxahJdpJxzCyY01sTljVjZsTTKD6DtAPjV/TjZYEiUxAEGTUv8pW/z+ksYobTGDxhmCKBopEKcJsORtOYEcAQMK5RlHu+nbnxM5LFCmY/Eu22AG7QB2x0N+RndVC72WxDlmtTj/CajrmqWQX2fBRbbcCIh2HqxYohR9NBBkvjlnAzHM6k4mWfKanYBMWXvtLyLNVi2DQSDTldQDGaYRU9OBUGrOUa95lMxm/qhcKe3ns8FFXwhJy2WCzWwDU4jCR0upSOxDAcwAfq/5rmxO0utKKhC2coCsfj/glSgMkE/oDjePwpaT1YakjxL3ffwzidzlsYqVKNNGxOJB5IkrzRJY1G3ptmF++5b/MXQB6kVy77fCaSBI5YdZDVuvnOIIllWXc+Xyq5/X4s2el0NEarFWpCGd3m+8OmFmwIRdt3d9Ppg84CytJuttsW7PTjAZXKlSrhbiqTAdnD/Anh5/O/ypEKjng72yKhTLL89hc3MaabVxm+awAAAABJRU5ErkJggg=="
><b><?= _PLW_NAME ?></b> &nbsp;<span class="w3-badge w3-<?= $g_theme[1]['span'] ?>"><?=
_PLW_VER ?></span> &nbsp; <a href="https://github.com/jyri78/plw" target="_blank">&#64;jyri78</a>
                </p>
            </div>
        </div>
    </footer>


</body>
</html>