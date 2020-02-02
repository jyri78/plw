<!DOCTYPE html>
<html lang="<?= APP_LANG ?>"<?= $_html ?>>
<head>
    <meta charset="UTF-8">
    <meta name="generator" content="<?= _PLW_NAME ?>">
    <meta name="author" content="Jüri Kormik">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <link rel="stylesheet" href="<?= PATH_WEB ?>?css">
    <title><?= $_title1 ?> – <?= $_title2 ?> | <?= INFO_COLLEGE ?></title>
</head>
<body<?= $_body ?>>


    <header class="w3-<?= defined('SUBJECT') ? 'container' : 'panel' ?> w3-round-large w3-<?=
$_hColor ?> w3-hover-shadow plw">
        <h1<?= $_hArgs ?>><?= $_hTitle ?></h1>
        <p <?= $_hpArgs ?>><?= $_hText ?></p>
    </header>
    <div class="w3-container"></div>
