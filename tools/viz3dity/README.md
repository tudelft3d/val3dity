
# viz3dity: a visualiser for val3dity errors 

![](screenshot.png)


## dependencies

```
pip install polyscope numpy click tqdm mapbox-earcut
```

## to view the errors

```
val3dity ../../data/rotterdam/3-20-DELFSHAVEN.city.json --report myreport.json
python viz3dity ../../data/rotterdam/3-20-DELFSHAVEN.city.json myreport.json
```
