const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>

<html lang="en" xmlns="http://www.w3.org/1999/xhtml">
<head>
    <meta charset="utf-8" />
    <title>Reflow Oven</title>
    <style type="text/css">
        canvas{
            border: 1px solid black;
            background: red;
        }
        body{
            margin: 0;
        }
    </style>
</head>
<body>
    <canvas></canvas>
    <script>
        var canvas = document.querySelector('canvas');
        canvas.width = window.innerWidth;
        canvas.height = window.innerHeight;
        var c = canvas.getContext('2d');
        c.fillRect(100, 100, 100, 100);

        console.log(canvas);
    </script>
</body>
</html>
)=====";