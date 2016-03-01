

a = imread('img/fruit.tif');
imshow(a)
an = gc_normalize_image(single(a));
seg = gc_mumford_shah(an, 4, 10);
figure; imshow(seg*64)
