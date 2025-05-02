ray.dof = 0;
ray.disH = 100000;
ray.tan =  1 / ray.tan;

if (sin(ray.ra) < -0.001)
{
    
    ray.ry = (((int)data->player.py >> 6) << 6) - 0.0001;
    ray.rx = (data->player.py - ray.ry) * ray.tan + data->player.px;
    ray.yo = -64;
    ray.xo = -ray.yo * ray.tan;
}
else if (sin(ray.ra) > 0.001)
{
    ray.ry = (((int)data->player.py >> 6) << 6) + 64;
    ray.rx = (data->player.py - ray.ry) * ray.tan + data->player.px;
    ray.yo = 64;
    ray.xo = -ray.yo * ray.tan;
}
else
{
    ray.rx = data->player.px;
    ray.ry = data->player.py;
    ray.dof = 8;
}
while (ray.dof < 8)
{
    ray.mx=(int)(ray.rx)>>6;
    ray.my=(int)(ray.ry)>>6;
    ray.mp=ray.my*MAP_HEIGHT+ray.mx;
    if (ray.mx >= 0 && ray.my >= 0 && ray.mx < MAP_WIDTH && ray.my < MAP_HEIGHT && data->map.arr[ray.my ][ray.mx] == '1')
    {
        ray.dof = 8;
        ray.disH = sqrt(pow(ray.rx - data->player.px, 2) + pow(ray.ry - data->player.py, 2));

    }
    else
    {
            ray.rx += ray.xo;
            ray.ry += ray.yo;
            ray.dof += 1;
    }

}