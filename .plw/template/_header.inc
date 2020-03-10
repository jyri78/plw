<!DOCTYPE html>
<html lang="<?= APP_LANG ?>"<?= $_html ?>>
<head>
    <meta charset="UTF-8">
    <meta name="generator" content="<?= _PLW_NAME ?>">
    <meta name="author" content="Jüri Kormik">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge"><?php
if ($g_inc == '_proj.inc'):
?>

    <script src="<?= PATH_WEB ?>?js<?php
    $js = PATH_MAIN . PROJECTS_FOLDER[0] .'/js/'. $g_proj .'.js';
    if ($g_proj && file_exists($js)) {
        echo '&'. PROJECTS_FOLDER[1] .'='. $g_proj;
    }
?>"></script><?php
endif;
?>

    <link rel="stylesheet" href="<?= PATH_WEB ?>?css">
    <title><?= $_title1 ?> – <?= $_title2 ?> | <?= INFO_COLLEGE ?></title>
</head>
<body<?= $_body ?>>


    <header class="w3-<?= defined('SUBJECT') ? 'container' : 'panel' ?> w3-round-large w3-<?=
$_hColor ?> w3-hover-shadow plw">
        <h1<?= $_hArgs ?>><?= $_hTitle ?></h1>
        <p <?= $_hpArgs ?>><?php
if (!defined('SUBJECT') && !empty(PROJECTS_FOLDER[0]) && file_exists(PATH_MAIN . PROJECTS_FOLDER[0])):
?>
<a href="<?= PATH_WEB . '?'. PROJECTS_FOLDER[1] ?>" class="w3-right" title="<?=
APP_WORDS[APP_LANG]['projects'] ?>">⌨</a><?php
endif;
?>
<?= $_hText ?></p>
    </header>
    <div class="w3-container"></div>
