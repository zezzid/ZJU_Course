'# MWS Version: Version 2019.0 - Sep 20 2018 - ACIS 28.0.2 -

'# length = mm
'# frequency = GHz
'# time = ns
'# frequency range: fmin = 8.2 fmax = 12.4
'# created = '[VERSION]2019.0|28.0.2|20180920[/VERSION]


'@ use template: Antenna - Waveguide.cfg

'[VERSION]2019.0|28.0.2|20180920[/VERSION]
'set the units
With Units
    .Geometry "mm"
    .Frequency "GHz"
    .Voltage "V"
    .Resistance "Ohm"
    .Inductance "NanoH"
    .TemperatureUnit  "Kelvin"
    .Time "ns"
    .Current "A"
    .Conductance "Siemens"
    .Capacitance "PikoF"
End With

'----------------------------------------------------------------------------

Plot.DrawBox True

With Background
     .Type "Normal"
     .Epsilon "1.0"
     .Mu "1.0"
     .XminSpace "0.0"
     .XmaxSpace "0.0"
     .YminSpace "0.0"
     .YmaxSpace "0.0"
     .ZminSpace "0.0"
     .ZmaxSpace "0.0"
End With

With Boundary
     .Xmin "expanded open"
     .Xmax "expanded open"
     .Ymin "expanded open"
     .Ymax "expanded open"
     .Zmin "expanded open"
     .Zmax "expanded open"
     .Xsymmetry "none"
     .Ysymmetry "none"
     .Zsymmetry "none"
End With

' switch on FD-TET setting for accurate farfields

FDSolver.ExtrudeOpenBC "True"

Mesh.FPBAAvoidNonRegUnite "True"
Mesh.ConsiderSpaceForLowerMeshLimit "False"
Mesh.MinimumStepNumber "5"

With MeshSettings
     .SetMeshType "Hex"
     .Set "RatioLimitGeometry", "20"
End With

With MeshSettings
     .SetMeshType "HexTLM"
     .Set "RatioLimitGeometry", "20"
End With

PostProcess1D.ActivateOperation "vswr", "true"
PostProcess1D.ActivateOperation "yz-matrices", "true"

With FarfieldPlot
	.ClearCuts ' lateral=phi, polar=theta
	.AddCut "lateral", "0", "1"
	.AddCut "lateral", "90", "1"
	.AddCut "polar", "90", "1"
End With

'----------------------------------------------------------------------------

With MeshSettings
     .SetMeshType "Hex"
     .Set "Version", 1%
End With

With Mesh
     .MeshType "PBA"
End With

'set the solver type
ChangeSolverType("HF Time Domain")

'----------------------------------------------------------------------------




'@ new component: component1

'[VERSION]2019.0|28.0.2|20180920[/VERSION]
Component.New "component1" 


'@ define brick: component1:solid1

'[VERSION]2019.0|28.0.2|20180920[/VERSION]
With Brick
     .Reset 
     .Name "solid1" 
     .Component "component1" 
     .Material "PEC" 
     .Xrange "-(a+t)/2", "(a+t)/2" 
     .Yrange "-(b+t)/2", "(b+t)/2" 
     .Zrange "-Lambda/2", "0" 
     .Create
End With


'@ define curve rectangle: curve1:rectangle1

'[VERSION]2019.0|28.0.2|20180920[/VERSION]
With Rectangle
     .Reset 
     .Name "rectangle1" 
     .Curve "curve1" 
     .Xrange "-(DH+t)/2", "(DH+t)/2" 
     .Yrange "-(DE+t)/2", "(DE+t)/2" 
     .Create
End With


'@ define coverprofile: component1:solid2

'[VERSION]2019.0|28.0.2|20180920[/VERSION]
With CoverCurve
     .Reset 
     .Name "solid2" 
     .Component "component1" 
     .Material "PEC" 
     .Curve "curve1:rectangle1" 
     .DeleteCurve "True" 
     .Create
End With


'@ pick face

'[VERSION]2019.0|28.0.2|20180920[/VERSION]
Pick.PickFaceFromId "component1:solid2", "1" 


'@ transform: translate component1:solid2

'[VERSION]2019.0|28.0.2|20180920[/VERSION]
With Transform 
     .Reset 
     .Name "component1:solid2" 
     .Vector "0", "0", "L" 
     .UsePickedPoints "False" 
     .InvertPickedPoints "False" 
     .MultipleObjects "False" 
     .GroupObjects "False" 
     .Repetitions "1" 
     .MultipleSelection "False" 
     .Transform "Shape", "Translate" 
End With 


'@ pick face

'[VERSION]2019.0|28.0.2|20180920[/VERSION]
Pick.PickFaceFromId "component1:solid2", "1" 


'@ pick face

'[VERSION]2019.0|28.0.2|20180920[/VERSION]
Pick.PickFaceFromId "component1:solid1", "1" 


'@ define loft: component1:solid3

'[VERSION]2019.0|28.0.2|20180920[/VERSION]
With Loft 
     .Reset 
     .Name "solid3" 
     .Component "component1" 
     .Material "PEC" 
     .Tangency "0.0" 
     .Minimizetwist "true" 
     .CreateNew 
End With 


'@ boolean add shapes: component1:solid1, component1:solid2

'[VERSION]2019.0|28.0.2|20180920[/VERSION]
Solid.Add "component1:solid1", "component1:solid2" 


'@ boolean add shapes: component1:solid1, component1:solid3

'[VERSION]2019.0|28.0.2|20180920[/VERSION]
Solid.Add "component1:solid1", "component1:solid3" 


'@ pick face

'[VERSION]2019.0|28.0.2|20180920[/VERSION]
Pick.PickFaceFromId "component1:solid1", "9" 


'@ pick face

'[VERSION]2019.0|28.0.2|20180920[/VERSION]
Pick.PickFaceFromId "component1:solid1", "7" 


'@ shell object: component1:solid1

'[VERSION]2019.0|28.0.2|20180920[/VERSION]
Solid.ShellAdvanced "component1:solid1", "Inside", "t", "True" 


'@ define frequency range

'[VERSION]2019.0|28.0.2|20180920[/VERSION]
Solver.FrequencyRange "8.2", "12.4" 


'@ pick face

'[VERSION]2019.0|28.0.2|20180920[/VERSION]
Pick.PickFaceFromId "component1:solid1", "9" 


'@ define port: 1

'[VERSION]2019.0|28.0.2|20180920[/VERSION]
With Port 
     .Reset 
     .PortNumber "1" 
     .Label "" 
     .Folder "" 
     .NumberOfModes "5" 
     .AdjustPolarization "False" 
     .PolarizationAngle "0.0" 
     .ReferencePlaneDistance "0" 
     .TextSize "50" 
     .TextMaxLimit "0" 
     .Coordinates "Picks" 
     .Orientation "positive" 
     .PortOnBound "False" 
     .ClipPickedPortToBound "False" 
     .Xrange "-11.93", "11.93" 
     .Yrange "-5.58", "5.58" 
     .Zrange "-14.55", "-14.55" 
     .XrangeAdd "0.0", "0.0" 
     .YrangeAdd "0.0", "0.0" 
     .ZrangeAdd "0.0", "0.0" 
     .SingleEnded "False" 
     .WaveguideMonitor "False" 
     .Create 
End With 


'@ define farfield monitor: farfield (f=10.3)

'[VERSION]2019.0|28.0.2|20180920[/VERSION]
With Monitor 
     .Reset 
     .Name "farfield (f=10.3)" 
     .Domain "Frequency" 
     .FieldType "Farfield" 
     .MonitorValue "10.3" 
     .ExportFarfieldSource "False" 
     .UseSubvolume "False" 
     .Coordinates "Structure" 
     .SetSubvolume "-40.5", "40.5", "-19.5", "19.5", "-14.55", "80" 
     .SetSubvolumeOffset "10", "10", "10", "10", "10", "10" 
     .SetSubvolumeInflateWithOffset "False" 
     .SetSubvolumeOffsetType "FractionOfWavelength" 
     .Create 
End With 


'@ define time domain solver parameters

'[VERSION]2019.0|28.0.2|20180920[/VERSION]
Mesh.SetCreator "High Frequency" 

With Solver 
     .Method "Hexahedral"
     .CalculationType "TD-S"
     .StimulationPort "All"
     .StimulationMode "All"
     .SteadyStateLimit "-30"
     .MeshAdaption "False"
     .AutoNormImpedance "False"
     .NormingImpedance "50"
     .CalculateModesOnly "True"
     .SParaSymmetry "False"
     .StoreTDResultsInCache  "False"
     .FullDeembedding "False"
     .SuperimposePLWExcitation "False"
     .UseSensitivityAnalysis "False"
End With


'@ set PBA version

'[VERSION]2019.0|28.0.2|20180920[/VERSION]
Discretizer.PBAVersion "2018092019"

'@ define time domain solver parameters

'[VERSION]2019.0|28.0.2|20180920[/VERSION]
Mesh.SetCreator "High Frequency" 

With Solver 
     .Method "Hexahedral"
     .CalculationType "TD-S"
     .StimulationPort "All"
     .StimulationMode "1"
     .SteadyStateLimit "-30"
     .MeshAdaption "False"
     .AutoNormImpedance "False"
     .NormingImpedance "50"
     .CalculateModesOnly "False"
     .SParaSymmetry "False"
     .StoreTDResultsInCache  "False"
     .FullDeembedding "False"
     .SuperimposePLWExcitation "False"
     .UseSensitivityAnalysis "False"
End With


'@ farfield plot options

'[VERSION]2019.0|28.0.2|20180920[/VERSION]
With FarfieldPlot 
     .Plottype "3D" 
     .Vary "angle1" 
     .Theta "90" 
     .Phi "90" 
     .Step "5" 
     .Step2 "5" 
     .SetLockSteps "True" 
     .SetPlotRangeOnly "False" 
     .SetThetaStart "0" 
     .SetThetaEnd "180" 
     .SetPhiStart "0" 
     .SetPhiEnd "360" 
     .SetTheta360 "False" 
     .SymmetricRange "False" 
     .SetTimeDomainFF "False" 
     .SetFrequency "10.3" 
     .SetTime "0" 
     .SetColorByValue "True" 
     .DrawStepLines "False" 
     .DrawIsoLongitudeLatitudeLines "False" 
     .ShowStructure "False" 
     .ShowStructureProfile "False" 
     .SetStructureTransparent "False" 
     .SetFarfieldTransparent "False" 
     .SetSpecials "enablepolarextralines" 
     .SetPlotMode "Gain" 
     .Distance "1" 
     .UseFarfieldApproximation "True" 
     .SetScaleLinear "False" 
     .SetLogRange "40" 
     .SetLogNorm "0" 
     .DBUnit "0" 
     .SetMaxReferenceMode "abs" 
     .EnableFixPlotMaximum "False" 
     .SetFixPlotMaximumValue "1" 
     .SetInverseAxialRatio "False" 
     .SetAxesType "user" 
     .SetAntennaType "unknown" 
     .Phistart "1.000000e+00", "0.000000e+00", "0.000000e+00" 
     .Thetastart "0.000000e+00", "0.000000e+00", "1.000000e+00" 
     .PolarizationVector "0.000000e+00", "1.000000e+00", "0.000000e+00" 
     .SetCoordinateSystemType "spherical" 
     .SetAutomaticCoordinateSystem "True" 
     .SetPolarizationType "Linear" 
     .SlantAngle 0.000000e+00 
     .Origin "bbox" 
     .Userorigin "0.000000e+00", "0.000000e+00", "0.000000e+00" 
     .SetUserDecouplingPlane "False" 
     .UseDecouplingPlane "False" 
     .DecouplingPlaneAxis "X" 
     .DecouplingPlanePosition "0.000000e+00" 
     .LossyGround "False" 
     .GroundEpsilon "1" 
     .GroundKappa "0" 
     .EnablePhaseCenterCalculation "False" 
     .SetPhaseCenterAngularLimit "3.000000e+01" 
     .SetPhaseCenterComponent "boresight" 
     .SetPhaseCenterPlane "both" 
     .ShowPhaseCenter "True" 
     .ClearCuts 
     .AddCut "lateral", "0", "1"  
     .AddCut "lateral", "90", "1"  
     .AddCut "polar", "90", "1"  

     .StoreSettings
End With 


