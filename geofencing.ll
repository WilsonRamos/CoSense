; ModuleID = '../geofencing.c'
source_filename = "../geofencing.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.GPSPoint = type { double, double, double, double, i32, double }
%struct.CircularGeofence = type { double, double, double }
%struct.RectangularGeofence = type { double, double, double, double }

@.str = private unnamed_addr constant [64 x i8] c"\F0\9F\9B\B0\EF\B8\8F  Iniciando simulaci\C3\B3n de procesamiento GPS optimizado\0A\00", align 1
@.str.1 = private unnamed_addr constant [61 x i8] c"\F0\9F\93\8A Usando especificaciones Newton DSL para optimizaci\C3\B3n\0A\0A\00", align 1
@__const.simulateGPSProcessing.test_points = private unnamed_addr constant [4 x %struct.GPSPoint] [%struct.GPSPoint { double 0xC030690A137F38C5, double 0xC051E1FB1C6B7091, double 2.345800e+03, double 0.000000e+00, i32 7, double 1.500000e+00 }, %struct.GPSPoint { double 0xC03069081C2E33F0, double 0xC051E1F9AA100962, double 2.348100e+03, double 1.200000e+00, i32 8, double 1.000000e+00 }, %struct.GPSPoint { double 0xC0306907E3235067, double 0xC051E1F96B25E8C8, double 2.350700e+03, double 5.000000e-01, i32 6, double 1.800000e+00 }, %struct.GPSPoint { double -1.641000e+01, double -7.153000e+01, double 2.400000e+03, double 5.000000e+00, i32 5, double 2.500000e+00 }], align 16
@.str.2 = private unnamed_addr constant [24 x i8] c"Punto %d: (%.6f, %.6f)\0A\00", align 1
@.str.3 = private unnamed_addr constant [31 x i8] c"  \E2\9D\8C Se\C3\B1al GPS insuficiente\0A\00", align 1
@.str.4 = private unnamed_addr constant [39 x i8] c"  \F0\9F\9A\AB Fuera de la zona de geofencing\0A\00", align 1
@.str.5 = private unnamed_addr constant [36 x i8] c"  \E2\9C\85 Dentro de zona 0 (est\C3\A1tico)\0A\00", align 1
@.str.6 = private unnamed_addr constant [41 x i8] c"  \F0\9F\8F\83 Dentro de zona 0 (en movimiento)\0A\00", align 1
@.str.7 = private unnamed_addr constant [19 x i8] c"  \F0\9F\93\8D En zona %d\0A\00", align 1
@.str.8 = private unnamed_addr constant [47 x i8] c"  \F0\9F\93\A1 Calidad GPS: %d, Velocidad: %.1f km/h\0A\0A\00", align 1
@.str.9 = private unnamed_addr constant [47 x i8] c"\F0\9F\9A\80 Geofencing GPS con Optimizaci\C3\B3n CoSense\0A\00", align 1
@.str.10 = private unnamed_addr constant [50 x i8] c"================================================\0A\00", align 1
@.str.11 = private unnamed_addr constant [71 x i8] c"\F0\9F\93\8B Este c\C3\B3digo usa tipos Newton DSL para optimizaci\C3\B3n autom\C3\A1tica\0A\00", align 1
@.str.12 = private unnamed_addr constant [64 x i8] c"\F0\9F\94\A7 CoSense optimizar\C3\A1 usando rangos GPS reales de Arequipa\0A\0A\00", align 1
@.str.13 = private unnamed_addr constant [28 x i8] c"\E2\9C\A8 Simulaci\C3\B3n completada\0A\00", align 1
@.str.14 = private unnamed_addr constant [34 x i8] c"\F0\9F\94\84 Para optimizar con CoSense:\0A\00", align 1
@.str.15 = private unnamed_addr constant [57 x i8] c"   1. clang -emit-llvm -S geofencing.c -o geofencing.ll\0A\00", align 1
@.str.16 = private unnamed_addr constant [44 x i8] c"   2. Aplicar CoSense con gps-specs.newton\0A\00", align 1
@.str.17 = private unnamed_addr constant [37 x i8] c"   3. Generar ejecutable optimizado\0A\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @calculateDistance(double %0, double %1, double %2, double %3) #0 {
  %5 = alloca double, align 8
  %6 = alloca double, align 8
  %7 = alloca double, align 8
  %8 = alloca double, align 8
  %9 = alloca double, align 8
  %10 = alloca double, align 8
  %11 = alloca double, align 8
  %12 = alloca double, align 8
  %13 = alloca double, align 8
  store double %0, double* %5, align 8
  store double %1, double* %6, align 8
  store double %2, double* %7, align 8
  store double %3, double* %8, align 8
  store double 6.371000e+06, double* %9, align 8
  %14 = load double, double* %7, align 8
  %15 = load double, double* %5, align 8
  %16 = fsub double %14, %15
  %17 = fmul double %16, 0x400921FB54442D18
  %18 = fdiv double %17, 1.800000e+02
  store double %18, double* %10, align 8
  %19 = load double, double* %8, align 8
  %20 = load double, double* %6, align 8
  %21 = fsub double %19, %20
  %22 = fmul double %21, 0x400921FB54442D18
  %23 = fdiv double %22, 1.800000e+02
  store double %23, double* %11, align 8
  %24 = load double, double* %10, align 8
  %25 = fdiv double %24, 2.000000e+00
  %26 = call double @sin(double %25) #4
  %27 = load double, double* %10, align 8
  %28 = fdiv double %27, 2.000000e+00
  %29 = call double @sin(double %28) #4
  %30 = fmul double %26, %29
  %31 = load double, double* %5, align 8
  %32 = fmul double %31, 0x400921FB54442D18
  %33 = fdiv double %32, 1.800000e+02
  %34 = call double @cos(double %33) #4
  %35 = load double, double* %7, align 8
  %36 = fmul double %35, 0x400921FB54442D18
  %37 = fdiv double %36, 1.800000e+02
  %38 = call double @cos(double %37) #4
  %39 = fmul double %34, %38
  %40 = load double, double* %11, align 8
  %41 = fdiv double %40, 2.000000e+00
  %42 = call double @sin(double %41) #4
  %43 = fmul double %39, %42
  %44 = load double, double* %11, align 8
  %45 = fdiv double %44, 2.000000e+00
  %46 = call double @sin(double %45) #4
  %47 = fmul double %43, %46
  %48 = fadd double %30, %47
  store double %48, double* %12, align 8
  %49 = load double, double* %12, align 8
  %50 = call double @sqrt(double %49) #4
  %51 = load double, double* %12, align 8
  %52 = fsub double 1.000000e+00, %51
  %53 = call double @sqrt(double %52) #4
  %54 = call double @atan2(double %50, double %53) #4
  %55 = fmul double 2.000000e+00, %54
  store double %55, double* %13, align 8
  %56 = load double, double* %13, align 8
  %57 = fmul double 6.371000e+06, %56
  ret double %57
}

; Function Attrs: nounwind
declare dso_local double @sin(double) #1

; Function Attrs: nounwind
declare dso_local double @cos(double) #1

; Function Attrs: nounwind
declare dso_local double @atan2(double, double) #1

; Function Attrs: nounwind
declare dso_local double @sqrt(double) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local zeroext i1 @isInsideCircularGeofence(double %0, double %1, %struct.CircularGeofence* %2) #0 {
  %4 = alloca double, align 8
  %5 = alloca double, align 8
  %6 = alloca %struct.CircularGeofence*, align 8
  %7 = alloca double, align 8
  store double %0, double* %4, align 8
  store double %1, double* %5, align 8
  store %struct.CircularGeofence* %2, %struct.CircularGeofence** %6, align 8
  %8 = load double, double* %4, align 8
  %9 = load double, double* %5, align 8
  %10 = load %struct.CircularGeofence*, %struct.CircularGeofence** %6, align 8
  %11 = getelementptr inbounds %struct.CircularGeofence, %struct.CircularGeofence* %10, i32 0, i32 0
  %12 = load double, double* %11, align 8
  %13 = load %struct.CircularGeofence*, %struct.CircularGeofence** %6, align 8
  %14 = getelementptr inbounds %struct.CircularGeofence, %struct.CircularGeofence* %13, i32 0, i32 1
  %15 = load double, double* %14, align 8
  %16 = call double @calculateDistance(double %8, double %9, double %12, double %15)
  store double %16, double* %7, align 8
  %17 = load double, double* %7, align 8
  %18 = load %struct.CircularGeofence*, %struct.CircularGeofence** %6, align 8
  %19 = getelementptr inbounds %struct.CircularGeofence, %struct.CircularGeofence* %18, i32 0, i32 2
  %20 = load double, double* %19, align 8
  %21 = fcmp ole double %17, %20
  ret i1 %21
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local zeroext i1 @isInsideRectangularGeofence(double %0, double %1, %struct.RectangularGeofence* %2) #0 {
  %4 = alloca i1, align 1
  %5 = alloca double, align 8
  %6 = alloca double, align 8
  %7 = alloca %struct.RectangularGeofence*, align 8
  store double %0, double* %5, align 8
  store double %1, double* %6, align 8
  store %struct.RectangularGeofence* %2, %struct.RectangularGeofence** %7, align 8
  %8 = load double, double* %5, align 8
  %9 = load %struct.RectangularGeofence*, %struct.RectangularGeofence** %7, align 8
  %10 = getelementptr inbounds %struct.RectangularGeofence, %struct.RectangularGeofence* %9, i32 0, i32 0
  %11 = load double, double* %10, align 8
  %12 = fcmp oge double %8, %11
  br i1 %12, label %13, label %32

13:                                               ; preds = %3
  %14 = load double, double* %5, align 8
  %15 = load %struct.RectangularGeofence*, %struct.RectangularGeofence** %7, align 8
  %16 = getelementptr inbounds %struct.RectangularGeofence, %struct.RectangularGeofence* %15, i32 0, i32 2
  %17 = load double, double* %16, align 8
  %18 = fcmp ole double %14, %17
  br i1 %18, label %19, label %32

19:                                               ; preds = %13
  %20 = load double, double* %6, align 8
  %21 = load %struct.RectangularGeofence*, %struct.RectangularGeofence** %7, align 8
  %22 = getelementptr inbounds %struct.RectangularGeofence, %struct.RectangularGeofence* %21, i32 0, i32 1
  %23 = load double, double* %22, align 8
  %24 = fcmp oge double %20, %23
  br i1 %24, label %25, label %32

25:                                               ; preds = %19
  %26 = load double, double* %6, align 8
  %27 = load %struct.RectangularGeofence*, %struct.RectangularGeofence** %7, align 8
  %28 = getelementptr inbounds %struct.RectangularGeofence, %struct.RectangularGeofence* %27, i32 0, i32 3
  %29 = load double, double* %28, align 8
  %30 = fcmp ole double %26, %29
  br i1 %30, label %31, label %32

31:                                               ; preds = %25
  store i1 true, i1* %4, align 1
  br label %33

32:                                               ; preds = %25, %19, %13, %3
  store i1 false, i1* %4, align 1
  br label %33

33:                                               ; preds = %32, %31
  %34 = load i1, i1* %4, align 1
  ret i1 %34
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local zeroext i1 @isVehicleMoving(double %0) #0 {
  %2 = alloca double, align 8
  %3 = alloca double, align 8
  store double %0, double* %2, align 8
  store double 1.000000e+00, double* %3, align 8
  %4 = load double, double* %2, align 8
  %5 = fcmp ogt double %4, 1.000000e+00
  ret i1 %5
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @evaluateGPSQuality(i32 %0, double %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca double, align 8
  store i32 %0, i32* %4, align 4
  store double %1, double* %5, align 8
  %6 = load i32, i32* %4, align 4
  %7 = icmp sge i32 %6, 8
  br i1 %7, label %8, label %12

8:                                                ; preds = %2
  %9 = load double, double* %5, align 8
  %10 = fcmp ole double %9, 1.000000e+00
  br i1 %10, label %11, label %12

11:                                               ; preds = %8
  store i32 3, i32* %3, align 4
  br label %27

12:                                               ; preds = %8, %2
  %13 = load i32, i32* %4, align 4
  %14 = icmp sge i32 %13, 6
  br i1 %14, label %15, label %19

15:                                               ; preds = %12
  %16 = load double, double* %5, align 8
  %17 = fcmp ole double %16, 1.500000e+00
  br i1 %17, label %18, label %19

18:                                               ; preds = %15
  store i32 2, i32* %3, align 4
  br label %27

19:                                               ; preds = %15, %12
  %20 = load i32, i32* %4, align 4
  %21 = icmp sge i32 %20, 4
  br i1 %21, label %22, label %26

22:                                               ; preds = %19
  %23 = load double, double* %5, align 8
  %24 = fcmp ole double %23, 2.000000e+00
  br i1 %24, label %25, label %26

25:                                               ; preds = %22
  store i32 1, i32* %3, align 4
  br label %27

26:                                               ; preds = %22, %19
  store i32 0, i32* %3, align 4
  br label %27

27:                                               ; preds = %26, %25, %18, %11
  %28 = load i32, i32* %3, align 4
  ret i32 %28
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @processGeofencing(%struct.GPSPoint* %0, %struct.CircularGeofence* %1, i32 %2) #0 {
  %4 = alloca i32, align 4
  %5 = alloca %struct.GPSPoint*, align 8
  %6 = alloca %struct.CircularGeofence*, align 8
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i8, align 1
  %10 = alloca i32, align 4
  store %struct.GPSPoint* %0, %struct.GPSPoint** %5, align 8
  store %struct.CircularGeofence* %1, %struct.CircularGeofence** %6, align 8
  store i32 %2, i32* %7, align 4
  %11 = load %struct.GPSPoint*, %struct.GPSPoint** %5, align 8
  %12 = getelementptr inbounds %struct.GPSPoint, %struct.GPSPoint* %11, i32 0, i32 4
  %13 = load i32, i32* %12, align 8
  %14 = load %struct.GPSPoint*, %struct.GPSPoint** %5, align 8
  %15 = getelementptr inbounds %struct.GPSPoint, %struct.GPSPoint* %14, i32 0, i32 5
  %16 = load double, double* %15, align 8
  %17 = call i32 @evaluateGPSQuality(i32 %13, double %16)
  store i32 %17, i32* %8, align 4
  %18 = load i32, i32* %8, align 4
  %19 = icmp slt i32 %18, 1
  br i1 %19, label %20, label %21

20:                                               ; preds = %3
  store i32 -1, i32* %4, align 4
  br label %56

21:                                               ; preds = %3
  %22 = load %struct.GPSPoint*, %struct.GPSPoint** %5, align 8
  %23 = getelementptr inbounds %struct.GPSPoint, %struct.GPSPoint* %22, i32 0, i32 3
  %24 = load double, double* %23, align 8
  %25 = call zeroext i1 @isVehicleMoving(double %24)
  %26 = zext i1 %25 to i8
  store i8 %26, i8* %9, align 1
  store i32 0, i32* %10, align 4
  br label %27

27:                                               ; preds = %52, %21
  %28 = load i32, i32* %10, align 4
  %29 = load i32, i32* %7, align 4
  %30 = icmp slt i32 %28, %29
  br i1 %30, label %31, label %55

31:                                               ; preds = %27
  %32 = load %struct.GPSPoint*, %struct.GPSPoint** %5, align 8
  %33 = getelementptr inbounds %struct.GPSPoint, %struct.GPSPoint* %32, i32 0, i32 0
  %34 = load double, double* %33, align 8
  %35 = load %struct.GPSPoint*, %struct.GPSPoint** %5, align 8
  %36 = getelementptr inbounds %struct.GPSPoint, %struct.GPSPoint* %35, i32 0, i32 1
  %37 = load double, double* %36, align 8
  %38 = load %struct.CircularGeofence*, %struct.CircularGeofence** %6, align 8
  %39 = load i32, i32* %10, align 4
  %40 = sext i32 %39 to i64
  %41 = getelementptr inbounds %struct.CircularGeofence, %struct.CircularGeofence* %38, i64 %40
  %42 = call zeroext i1 @isInsideCircularGeofence(double %34, double %37, %struct.CircularGeofence* %41)
  br i1 %42, label %43, label %51

43:                                               ; preds = %31
  %44 = load i8, i8* %9, align 1
  %45 = trunc i8 %44 to i1
  br i1 %45, label %46, label %49

46:                                               ; preds = %43
  %47 = load i32, i32* %10, align 4
  %48 = add nsw i32 %47, 100
  store i32 %48, i32* %4, align 4
  br label %56

49:                                               ; preds = %43
  %50 = load i32, i32* %10, align 4
  store i32 %50, i32* %4, align 4
  br label %56

51:                                               ; preds = %31
  br label %52

52:                                               ; preds = %51
  %53 = load i32, i32* %10, align 4
  %54 = add nsw i32 %53, 1
  store i32 %54, i32* %10, align 4
  br label %27

55:                                               ; preds = %27
  store i32 -2, i32* %4, align 4
  br label %56

56:                                               ; preds = %55, %49, %46, %20
  %57 = load i32, i32* %4, align 4
  ret i32 %57
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @createArequipaGeofence(%struct.CircularGeofence* noalias sret %0) #0 {
  %2 = getelementptr inbounds %struct.CircularGeofence, %struct.CircularGeofence* %0, i32 0, i32 0
  store double 0xC0306907E3235067, double* %2, align 8
  %3 = getelementptr inbounds %struct.CircularGeofence, %struct.CircularGeofence* %0, i32 0, i32 1
  store double 0xC051E1FA1D67EFD3, double* %3, align 8
  %4 = getelementptr inbounds %struct.CircularGeofence, %struct.CircularGeofence* %0, i32 0, i32 2
  store double 1.000000e+02, double* %4, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @simulateGPSProcessing() #0 {
  %1 = alloca %struct.CircularGeofence, align 8
  %2 = alloca [4 x %struct.GPSPoint], align 16
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([64 x i8], [64 x i8]* @.str, i64 0, i64 0))
  %7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([61 x i8], [61 x i8]* @.str.1, i64 0, i64 0))
  call void @createArequipaGeofence(%struct.CircularGeofence* sret %1)
  %8 = bitcast [4 x %struct.GPSPoint]* %2 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 16 %8, i8* align 16 bitcast ([4 x %struct.GPSPoint]* @__const.simulateGPSProcessing.test_points to i8*), i64 192, i1 false)
  store i32 4, i32* %3, align 4
  store i32 0, i32* %4, align 4
  br label %9

9:                                                ; preds = %61, %0
  %10 = load i32, i32* %4, align 4
  %11 = load i32, i32* %3, align 4
  %12 = icmp slt i32 %10, %11
  br i1 %12, label %13, label %64

13:                                               ; preds = %9
  %14 = load i32, i32* %4, align 4
  %15 = add nsw i32 %14, 1
  %16 = load i32, i32* %4, align 4
  %17 = sext i32 %16 to i64
  %18 = getelementptr inbounds [4 x %struct.GPSPoint], [4 x %struct.GPSPoint]* %2, i64 0, i64 %17
  %19 = getelementptr inbounds %struct.GPSPoint, %struct.GPSPoint* %18, i32 0, i32 0
  %20 = load double, double* %19, align 16
  %21 = load i32, i32* %4, align 4
  %22 = sext i32 %21 to i64
  %23 = getelementptr inbounds [4 x %struct.GPSPoint], [4 x %struct.GPSPoint]* %2, i64 0, i64 %22
  %24 = getelementptr inbounds %struct.GPSPoint, %struct.GPSPoint* %23, i32 0, i32 1
  %25 = load double, double* %24, align 8
  %26 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.2, i64 0, i64 0), i32 %15, double %20, double %25)
  %27 = load i32, i32* %4, align 4
  %28 = sext i32 %27 to i64
  %29 = getelementptr inbounds [4 x %struct.GPSPoint], [4 x %struct.GPSPoint]* %2, i64 0, i64 %28
  %30 = call i32 @processGeofencing(%struct.GPSPoint* %29, %struct.CircularGeofence* %1, i32 1)
  store i32 %30, i32* %5, align 4
  %31 = load i32, i32* %5, align 4
  switch i32 %31, label %40 [
    i32 -1, label %32
    i32 -2, label %34
    i32 0, label %36
    i32 100, label %38
  ]

32:                                               ; preds = %13
  %33 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.3, i64 0, i64 0))
  br label %43

34:                                               ; preds = %13
  %35 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.4, i64 0, i64 0))
  br label %43

36:                                               ; preds = %13
  %37 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.5, i64 0, i64 0))
  br label %43

38:                                               ; preds = %13
  %39 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.6, i64 0, i64 0))
  br label %43

40:                                               ; preds = %13
  %41 = load i32, i32* %5, align 4
  %42 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.7, i64 0, i64 0), i32 %41)
  br label %43

43:                                               ; preds = %40, %38, %36, %34, %32
  %44 = load i32, i32* %4, align 4
  %45 = sext i32 %44 to i64
  %46 = getelementptr inbounds [4 x %struct.GPSPoint], [4 x %struct.GPSPoint]* %2, i64 0, i64 %45
  %47 = getelementptr inbounds %struct.GPSPoint, %struct.GPSPoint* %46, i32 0, i32 4
  %48 = load i32, i32* %47, align 16
  %49 = load i32, i32* %4, align 4
  %50 = sext i32 %49 to i64
  %51 = getelementptr inbounds [4 x %struct.GPSPoint], [4 x %struct.GPSPoint]* %2, i64 0, i64 %50
  %52 = getelementptr inbounds %struct.GPSPoint, %struct.GPSPoint* %51, i32 0, i32 5
  %53 = load double, double* %52, align 8
  %54 = call i32 @evaluateGPSQuality(i32 %48, double %53)
  %55 = load i32, i32* %4, align 4
  %56 = sext i32 %55 to i64
  %57 = getelementptr inbounds [4 x %struct.GPSPoint], [4 x %struct.GPSPoint]* %2, i64 0, i64 %56
  %58 = getelementptr inbounds %struct.GPSPoint, %struct.GPSPoint* %57, i32 0, i32 3
  %59 = load double, double* %58, align 8
  %60 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.8, i64 0, i64 0), i32 %54, double %59)
  br label %61

61:                                               ; preds = %43
  %62 = load i32, i32* %4, align 4
  %63 = add nsw i32 %62, 1
  store i32 %63, i32* %4, align 4
  br label %9

64:                                               ; preds = %9
  ret void
}

declare dso_local i32 @printf(i8*, ...) #2

; Function Attrs: argmemonly nounwind willreturn
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* noalias nocapture writeonly, i8* noalias nocapture readonly, i64, i1 immarg) #3

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.9, i64 0, i64 0))
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([50 x i8], [50 x i8]* @.str.10, i64 0, i64 0))
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([71 x i8], [71 x i8]* @.str.11, i64 0, i64 0))
  %5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([64 x i8], [64 x i8]* @.str.12, i64 0, i64 0))
  call void @simulateGPSProcessing()
  %6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.13, i64 0, i64 0))
  %7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.14, i64 0, i64 0))
  %8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([57 x i8], [57 x i8]* @.str.15, i64 0, i64 0))
  %9 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.16, i64 0, i64 0))
  %10 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.17, i64 0, i64 0))
  ret i32 0
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { argmemonly nounwind willreturn }
attributes #4 = { nounwind }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 10.0.0-4ubuntu1 "}
