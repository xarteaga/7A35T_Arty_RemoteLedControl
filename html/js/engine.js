/**
 * Created by xavier on 12/08/2016.
 */
var HW_IPADDR = "192.168.1.10";

var WR_WIDTH = 200,
    WR_HEIGHT = 234,
    CV_MARGIN = 10,
    CV_SCALE = 3;

var list_compartments = [
    {
        posx: 2,
        posy: 2,
        width: 96,
        height: 42
    },
    {
        posx: 2,
        posy: 46,
        width: 96,
        height: 120
    },
    {
        posx: 2,
        posy: 168,
        width: 96,
        height: 60
    },
    {
        posx: 102,
        posy: 2,
        width: 46,
        height: 42
    },
    {
        posx: 102,
        posy: 46,
        width: 46,
        height: 42
    },
    {
        posx: 102,
        posy: 90,
        width: 46,
        height: 42
    },
    {
        posx: 102,
        posy: 134,
        width: 46,
        height: 42
    },
    {
        posx: 152,
        posy: 2,
        width: 46,
        height: 42
    },
    {
        posx: 152,
        posy: 46,
        width: 46,
        height: 100
    },
    {
        posx: 152,
        posy: 148,
        width: 46,
        height: 80
    }
];

function hslToRgb(h, s, l){
    var r, g, b;

    if(s == 0){
        r = g = b = l; // achromatic
    }else{
        var hue2rgb = function hue2rgb(p, q, t){
            if(t < 0) t += 1;
            if(t > 1) t -= 1;
            if(t < 1/6) return p + (q - p) * 6 * t;
            if(t < 1/2) return q;
            if(t < 2/3) return p + (q - p) * (2/3 - t) * 6;
            return p;
        }

        var q = l < 0.5 ? l * (1 + s) : l + s - l * s;
        var p = 2 * l - q;
        r = hue2rgb(p, q, h + 1/3);
        g = hue2rgb(p, q, h);
        b = hue2rgb(p, q, h - 1/3);
    }

    return [Math.round(r * 255), Math.round(g * 255), Math.round(b * 255)];
}

function init () {
    /* Set base */
    wardrobe_base = $(".wardrobe_base");
    wardrobe_base.width((WR_WIDTH*CV_SCALE + 2*CV_MARGIN) + "px");
    wardrobe_base.height((WR_HEIGHT*CV_SCALE + 2*CV_MARGIN) + "px");

    list_compartments.forEach(function (e, i) {
        var div = document.createElement('div');
        div.className = "shelve_base";
        div.id = "shelve_" + i;
        wardrobe_base[0].appendChild(div);

        var label = document.createElement('span');
        label.className = "shelve_label";
        label.id = "shelve_label_" + i;
        label.innerHTML = i;
        div.appendChild(label);

        div = $("#shelve_" + i);
        div.css("left", (e.posx*CV_SCALE + CV_MARGIN) + "px");
        div.css("top", (e.posy*CV_SCALE + CV_MARGIN) + "px");
        div.css("height", (e.height*CV_SCALE) + "px");
        div.css("width", (e.width*CV_SCALE) + "px");
        div.attr("onclick", "pick_color("+ i +")");
    });
}

window.addEventListener("resize", function(){
    color_picker_base = $(".color_picker_base");

    color_picker_base.width($(".modal-body")[0].offsetWidth + "px");
    color_picker_base.height($(".modal-body")[0].offsetWidt + "px");

});

function toHexStr(x){
    var temp = x.toString(16);

    if (temp.length < 2){
        temp = "0" + temp;
    }

    return temp;
}

function set_color (chan, hexcode) {
    $.get("http://" + HW_IPADDR + "/pwm/" + chan + "/rgb/x" + hexcode, function(pwm_list){

        pwm_list.forEach(function(e, i){
            $("#shelve_"+i).css("background-color", "#" + toHexStr(e.r) + toHexStr(e.g) + toHexStr(e.b));
        });
    });
    $("#myModal").modal('hide');
}

function pick_color (chan) {
    $("#myModal").modal();

    color_picker_base = $(".color_picker_base");

    color_picker_base.width($(".modal-body")[0].offsetWidth + "px");
    color_picker_base.height($(".modal-body")[0].offsetWidt + "px");

    while (color_picker_base[0].firstChild) {
        color_picker_base[0].removeChild(color_picker_base[0].firstChild);
    }

    var col = 0;
    var row = 0;
    var tile_width = 100/Math.floor(20);
    var tile_height = 100/Math.floor(9);
    for (var h =0 ; h < 100; h = h + 5){
        for (var s =99 ; s < 100; s = s + 40) {
            row = 0;

            for (var l =10 ; l < 100; l = l + 10) {
                var temp = hslToRgb(h/100, s/100, l/100);
                r = temp[0];
                g = temp[1];
                b = temp[2];
                var id = "color_" + toHexStr(r) + toHexStr(g) + toHexStr(b);
                var div = document.createElement('div');
                div.setAttribute("color", "#" + r.toString(16) + g.toString(16) + b.toString(16));
                div.className = "color_picker_tile hexagon";
                div.id = id;

                color_picker_base[0].appendChild(div);

                div = $("#" + id);
                div.css("background-color", "rgb(" + r.toString() + ", " + g.toString() + ", " + b.toString()+ ")");
                div.css("left", (col * tile_width + 0.05*tile_width) + "%");
                div.css("top", (row * tile_height + 0.05*tile_height) + "%");
                div.css("height", 0.9*tile_height + "%");
                div.css("width", 0.9*tile_width + "%");
                div.attr("onclick", "set_color("+ chan +", '"+ toHexStr(r) + toHexStr(g) + toHexStr(b) +"')");
                row++;
            }
            col ++;
        }
    }
}

/* Init block */
init();