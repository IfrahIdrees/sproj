; ModuleID = 'calc.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.process = type { %struct.process*, i8*, i8 (%struct.pt*, i8, i8*)*, %struct.pt, i8, i8 }
%struct.pt = type { i16 }
%struct.ctk_window = type { %struct.ctk_window*, %struct.ctk_window*, %struct.ctk_desktop*, %struct.process*, i8*, i8, %struct.ctk_label, %struct.ctk_label, i8, i8, %struct.ctk_widget*, %struct.ctk_widget*, %struct.ctk_widget* }
%struct.ctk_desktop = type { i8*, %struct.ctk_window, %struct.ctk_window*, %struct.ctk_window*, i8, i8, i8, [8 x %struct.ctk_widget*], i8, [8 x %struct.ctk_window*], i8, i8, i8 }
%struct.ctk_label = type { %struct.ctk_widget*, %struct.ctk_window*, i8, i8, i8, i8, i8, i8* }
%struct.ctk_widget = type { %struct.ctk_widget*, %struct.ctk_window*, i8, i8, i8, i8, i8, %union.anon }
%union.anon = type { %struct.ctk_widget_icon }
%struct.ctk_widget_icon = type { i8*, %struct.process*, i8*, i8* }
%struct.ctk_button = type { %struct.ctk_widget*, %struct.ctk_window*, i8, i8, i8, i8, i8, i8* }

@.str = private unnamed_addr constant [11 x i8] c"Calculator\00", align 1
@calc_process = global { %struct.process*, i8*, i8 (%struct.pt*, i8, i8*)*, %struct.pt, i8, i8, [4 x i8] } { %struct.process* null, i8* getelementptr inbounds ([11 x i8]* @.str, i32 0, i32 0), i8 (%struct.pt*, i8, i8*)* @process_thread_calc_process, %struct.pt zeroinitializer, i8 0, i8 0, [4 x i8] undef }, align 8
@window = internal global %struct.ctk_window zeroinitializer, align 8
@.str1 = private unnamed_addr constant [5 x i8] c"Calc\00", align 1
@inputlabel = internal global %struct.ctk_label { %struct.ctk_widget* null, %struct.ctk_window* null, i8 0, i8 0, i8 2, i8 12, i8 1, i8* getelementptr inbounds ([16 x i8]* @input, i32 0, i32 0) }, align 8
@cbutton = internal global %struct.ctk_button { %struct.ctk_widget* null, %struct.ctk_window* null, i8 0, i8 2, i8 3, i8 1, i8 1, i8* getelementptr inbounds ([2 x i8]* @.str17, i32 0, i32 0) }, align 8
@divbutton = internal global %struct.ctk_button { %struct.ctk_widget* null, %struct.ctk_window* null, i8 9, i8 2, i8 3, i8 1, i8 1, i8* getelementptr inbounds ([2 x i8]* @.str16, i32 0, i32 0) }, align 8
@button7 = internal global %struct.ctk_button { %struct.ctk_widget* null, %struct.ctk_window* null, i8 0, i8 3, i8 3, i8 1, i8 1, i8* getelementptr inbounds ([2 x i8]* @.str15, i32 0, i32 0) }, align 8
@button8 = internal global %struct.ctk_button { %struct.ctk_widget* null, %struct.ctk_window* null, i8 3, i8 3, i8 3, i8 1, i8 1, i8* getelementptr inbounds ([2 x i8]* @.str14, i32 0, i32 0) }, align 8
@button9 = internal global %struct.ctk_button { %struct.ctk_widget* null, %struct.ctk_window* null, i8 6, i8 3, i8 3, i8 1, i8 1, i8* getelementptr inbounds ([2 x i8]* @.str13, i32 0, i32 0) }, align 8
@mulbutton = internal global %struct.ctk_button { %struct.ctk_widget* null, %struct.ctk_window* null, i8 9, i8 3, i8 3, i8 1, i8 1, i8* getelementptr inbounds ([2 x i8]* @.str12, i32 0, i32 0) }, align 8
@button4 = internal global %struct.ctk_button { %struct.ctk_widget* null, %struct.ctk_window* null, i8 0, i8 4, i8 3, i8 1, i8 1, i8* getelementptr inbounds ([2 x i8]* @.str11, i32 0, i32 0) }, align 8
@button5 = internal global %struct.ctk_button { %struct.ctk_widget* null, %struct.ctk_window* null, i8 3, i8 4, i8 3, i8 1, i8 1, i8* getelementptr inbounds ([2 x i8]* @.str10, i32 0, i32 0) }, align 8
@button6 = internal global %struct.ctk_button { %struct.ctk_widget* null, %struct.ctk_window* null, i8 6, i8 4, i8 3, i8 1, i8 1, i8* getelementptr inbounds ([2 x i8]* @.str9, i32 0, i32 0) }, align 8
@subbutton = internal global %struct.ctk_button { %struct.ctk_widget* null, %struct.ctk_window* null, i8 9, i8 4, i8 3, i8 1, i8 1, i8* getelementptr inbounds ([2 x i8]* @.str8, i32 0, i32 0) }, align 8
@button1 = internal global %struct.ctk_button { %struct.ctk_widget* null, %struct.ctk_window* null, i8 0, i8 5, i8 3, i8 1, i8 1, i8* getelementptr inbounds ([2 x i8]* @.str7, i32 0, i32 0) }, align 8
@button2 = internal global %struct.ctk_button { %struct.ctk_widget* null, %struct.ctk_window* null, i8 3, i8 5, i8 3, i8 1, i8 1, i8* getelementptr inbounds ([2 x i8]* @.str6, i32 0, i32 0) }, align 8
@button3 = internal global %struct.ctk_button { %struct.ctk_widget* null, %struct.ctk_window* null, i8 6, i8 5, i8 3, i8 1, i8 1, i8* getelementptr inbounds ([2 x i8]* @.str5, i32 0, i32 0) }, align 8
@addbutton = internal global %struct.ctk_button { %struct.ctk_widget* null, %struct.ctk_window* null, i8 9, i8 5, i8 3, i8 1, i8 1, i8* getelementptr inbounds ([2 x i8]* @.str4, i32 0, i32 0) }, align 8
@button0 = internal global %struct.ctk_button { %struct.ctk_widget* null, %struct.ctk_window* null, i8 0, i8 6, i8 3, i8 3, i8 1, i8* getelementptr inbounds ([4 x i8]* @.str3, i32 0, i32 0) }, align 8
@calcbutton = internal global %struct.ctk_button { %struct.ctk_widget* null, %struct.ctk_window* null, i8 9, i8 6, i8 3, i8 1, i8 1, i8* getelementptr inbounds ([2 x i8]* @.str2, i32 0, i32 0) }, align 8
@ctk_signal_keypress = external global i8
@op = internal global i8 0, align 1
@ctk_signal_button_activate = external global i8
@ctk_signal_window_close = external global i8
@operand1 = internal global i64 0, align 8
@operand2 = internal global i64 0, align 8
@input = internal global [16 x i8] zeroinitializer, align 16
@.str2 = private unnamed_addr constant [2 x i8] c"=\00", align 1
@.str3 = private unnamed_addr constant [4 x i8] c" 0 \00", align 1
@.str4 = private unnamed_addr constant [2 x i8] c"+\00", align 1
@.str5 = private unnamed_addr constant [2 x i8] c"3\00", align 1
@.str6 = private unnamed_addr constant [2 x i8] c"2\00", align 1
@.str7 = private unnamed_addr constant [2 x i8] c"1\00", align 1
@.str8 = private unnamed_addr constant [2 x i8] c"-\00", align 1
@.str9 = private unnamed_addr constant [2 x i8] c"6\00", align 1
@.str10 = private unnamed_addr constant [2 x i8] c"5\00", align 1
@.str11 = private unnamed_addr constant [2 x i8] c"4\00", align 1
@.str12 = private unnamed_addr constant [2 x i8] c"*\00", align 1
@.str13 = private unnamed_addr constant [2 x i8] c"9\00", align 1
@.str14 = private unnamed_addr constant [2 x i8] c"8\00", align 1
@.str15 = private unnamed_addr constant [2 x i8] c"7\00", align 1
@.str16 = private unnamed_addr constant [2 x i8] c"/\00", align 1
@.str17 = private unnamed_addr constant [2 x i8] c"C\00", align 1

; Function Attrs: nounwind uwtable
define internal signext i8 @process_thread_calc_process(%struct.pt* %process_pt, i8 zeroext %ev, i8* %data) #0 {
  %1 = alloca i8, align 1
  %2 = alloca %struct.pt*, align 8
  %3 = alloca i8, align 1
  %4 = alloca i8*, align 8
  %PT_YIELD_FLAG = alloca i8, align 1
  store %struct.pt* %process_pt, %struct.pt** %2, align 8
  store i8 %ev, i8* %3, align 1
  store i8* %data, i8** %4, align 8
  store i8 1, i8* %PT_YIELD_FLAG, align 1
  %5 = load i8* %PT_YIELD_FLAG, align 1
  %6 = icmp ne i8 %5, 0
  br i1 %6, label %7, label %8

; <label>:7                                       ; preds = %0
  br label %8

; <label>:8                                       ; preds = %7, %0
  %9 = load %struct.pt** %2, align 8
  %10 = getelementptr inbounds %struct.pt* %9, i32 0, i32 0
  %11 = load i16* %10, align 2
  %12 = zext i16 %11 to i32
  switch i32 %12, label %200 [
    i32 0, label %13
    i32 224, label %18
  ]

; <label>:13                                      ; preds = %8
  call void @ctk_window_new(%struct.ctk_window* @window, i8 zeroext 12, i8 zeroext 7, i8* getelementptr inbounds ([5 x i8]* @.str1, i32 0, i32 0))
  call void @ctk_widget_add(%struct.ctk_window* @window, %struct.ctk_widget* bitcast (%struct.ctk_label* @inputlabel to %struct.ctk_widget*))
  call void @ctk_widget_add(%struct.ctk_window* @window, %struct.ctk_widget* bitcast (%struct.ctk_button* @cbutton to %struct.ctk_widget*))
  call void @ctk_widget_add(%struct.ctk_window* @window, %struct.ctk_widget* bitcast (%struct.ctk_button* @divbutton to %struct.ctk_widget*))
  call void @ctk_widget_add(%struct.ctk_window* @window, %struct.ctk_widget* bitcast (%struct.ctk_button* @button7 to %struct.ctk_widget*))
  call void @ctk_widget_add(%struct.ctk_window* @window, %struct.ctk_widget* bitcast (%struct.ctk_button* @button8 to %struct.ctk_widget*))
  call void @ctk_widget_add(%struct.ctk_window* @window, %struct.ctk_widget* bitcast (%struct.ctk_button* @button9 to %struct.ctk_widget*))
  call void @ctk_widget_add(%struct.ctk_window* @window, %struct.ctk_widget* bitcast (%struct.ctk_button* @mulbutton to %struct.ctk_widget*))
  call void @ctk_widget_add(%struct.ctk_window* @window, %struct.ctk_widget* bitcast (%struct.ctk_button* @button4 to %struct.ctk_widget*))
  call void @ctk_widget_add(%struct.ctk_window* @window, %struct.ctk_widget* bitcast (%struct.ctk_button* @button5 to %struct.ctk_widget*))
  call void @ctk_widget_add(%struct.ctk_window* @window, %struct.ctk_widget* bitcast (%struct.ctk_button* @button6 to %struct.ctk_widget*))
  call void @ctk_widget_add(%struct.ctk_window* @window, %struct.ctk_widget* bitcast (%struct.ctk_button* @subbutton to %struct.ctk_widget*))
  call void @ctk_widget_add(%struct.ctk_window* @window, %struct.ctk_widget* bitcast (%struct.ctk_button* @button1 to %struct.ctk_widget*))
  call void @ctk_widget_add(%struct.ctk_window* @window, %struct.ctk_widget* bitcast (%struct.ctk_button* @button2 to %struct.ctk_widget*))
  call void @ctk_widget_add(%struct.ctk_window* @window, %struct.ctk_widget* bitcast (%struct.ctk_button* @button3 to %struct.ctk_widget*))
  call void @ctk_widget_add(%struct.ctk_window* @window, %struct.ctk_widget* bitcast (%struct.ctk_button* @addbutton to %struct.ctk_widget*))
  call void @ctk_widget_add(%struct.ctk_window* @window, %struct.ctk_widget* bitcast (%struct.ctk_button* @button0 to %struct.ctk_widget*))
  call void @ctk_widget_add(%struct.ctk_window* @window, %struct.ctk_widget* bitcast (%struct.ctk_button* @calcbutton to %struct.ctk_widget*))
  call void @clear_input()
  call void @ctk_window_open(%struct.ctk_window* @window)
  br label %14

; <label>:14                                      ; preds = %13, %199
  br label %15

; <label>:15                                      ; preds = %14
  store i8 0, i8* %PT_YIELD_FLAG, align 1
  %16 = load %struct.pt** %2, align 8
  %17 = getelementptr inbounds %struct.pt* %16, i32 0, i32 0
  store i16 224, i16* %17, align 2
  br label %18

; <label>:18                                      ; preds = %8, %15
  %19 = load i8* %PT_YIELD_FLAG, align 1
  %20 = sext i8 %19 to i32
  %21 = icmp eq i32 %20, 0
  br i1 %21, label %22, label %23

; <label>:22                                      ; preds = %18
  store i8 1, i8* %1
  br label %203

; <label>:23                                      ; preds = %18
  br label %24

; <label>:24                                      ; preds = %23
  %25 = load i8* %3, align 1
  %26 = zext i8 %25 to i32
  %27 = load i8* @ctk_signal_keypress, align 1
  %28 = zext i8 %27 to i32
  %29 = icmp eq i32 %26, %28
  br i1 %29, label %30, label %101

; <label>:30                                      ; preds = %24
  %31 = load i8** %4, align 8
  %32 = ptrtoint i8* %31 to i64
  %33 = trunc i64 %32 to i8
  %34 = sext i8 %33 to i32
  %35 = icmp sge i32 %34, 48
  br i1 %35, label %36, label %46

; <label>:36                                      ; preds = %30
  %37 = load i8** %4, align 8
  %38 = ptrtoint i8* %37 to i64
  %39 = trunc i64 %38 to i8
  %40 = sext i8 %39 to i32
  %41 = icmp sle i32 %40, 57
  br i1 %41, label %42, label %46

; <label>:42                                      ; preds = %36
  %43 = load i8** %4, align 8
  %44 = ptrtoint i8* %43 to i64
  %45 = trunc i64 %44 to i8
  call void @add_to_input(i8 signext %45)
  br label %100

; <label>:46                                      ; preds = %36, %30
  %47 = load i8** %4, align 8
  %48 = ptrtoint i8* %47 to i64
  %49 = trunc i64 %48 to i8
  %50 = sext i8 %49 to i32
  %51 = icmp eq i32 %50, 32
  br i1 %51, label %52, label %53

; <label>:52                                      ; preds = %46
  call void @clear_input()
  br label %99

; <label>:53                                      ; preds = %46
  %54 = load i8** %4, align 8
  %55 = ptrtoint i8* %54 to i64
  %56 = trunc i64 %55 to i8
  %57 = sext i8 %56 to i32
  %58 = icmp eq i32 %57, 43
  br i1 %58, label %59, label %60

; <label>:59                                      ; preds = %53
  call void @input_to_operand1()
  store i8 1, i8* @op, align 1
  br label %98

; <label>:60                                      ; preds = %53
  %61 = load i8** %4, align 8
  %62 = ptrtoint i8* %61 to i64
  %63 = trunc i64 %62 to i8
  %64 = sext i8 %63 to i32
  %65 = icmp eq i32 %64, 45
  br i1 %65, label %66, label %67

; <label>:66                                      ; preds = %60
  call void @input_to_operand1()
  store i8 2, i8* @op, align 1
  br label %97

; <label>:67                                      ; preds = %60
  %68 = load i8** %4, align 8
  %69 = ptrtoint i8* %68 to i64
  %70 = trunc i64 %69 to i8
  %71 = sext i8 %70 to i32
  %72 = icmp eq i32 %71, 42
  br i1 %72, label %73, label %74

; <label>:73                                      ; preds = %67
  call void @input_to_operand1()
  store i8 3, i8* @op, align 1
  br label %96

; <label>:74                                      ; preds = %67
  %75 = load i8** %4, align 8
  %76 = ptrtoint i8* %75 to i64
  %77 = trunc i64 %76 to i8
  %78 = sext i8 %77 to i32
  %79 = icmp eq i32 %78, 47
  br i1 %79, label %80, label %81

; <label>:80                                      ; preds = %74
  call void @input_to_operand1()
  store i8 4, i8* @op, align 1
  br label %95

; <label>:81                                      ; preds = %74
  %82 = load i8** %4, align 8
  %83 = ptrtoint i8* %82 to i64
  %84 = trunc i64 %83 to i8
  %85 = sext i8 %84 to i32
  %86 = icmp eq i32 %85, 61
  br i1 %86, label %93, label %87

; <label>:87                                      ; preds = %81
  %88 = load i8** %4, align 8
  %89 = ptrtoint i8* %88 to i64
  %90 = trunc i64 %89 to i8
  %91 = sext i8 %90 to i32
  %92 = icmp eq i32 %91, 10
  br i1 %92, label %93, label %94

; <label>:93                                      ; preds = %87, %81
  call void @calculate()
  br label %94

; <label>:94                                      ; preds = %93, %87
  br label %95

; <label>:95                                      ; preds = %94, %80
  br label %96

; <label>:96                                      ; preds = %95, %73
  br label %97

; <label>:97                                      ; preds = %96, %66
  br label %98

; <label>:98                                      ; preds = %97, %59
  br label %99

; <label>:99                                      ; preds = %98, %52
  br label %100

; <label>:100                                     ; preds = %99, %42
  call void @ctk_widget_redraw(%struct.ctk_widget* bitcast (%struct.ctk_label* @inputlabel to %struct.ctk_widget*))
  br label %199

; <label>:101                                     ; preds = %24
  %102 = load i8* %3, align 1
  %103 = zext i8 %102 to i32
  %104 = load i8* @ctk_signal_button_activate, align 1
  %105 = zext i8 %104 to i32
  %106 = icmp eq i32 %103, %105
  br i1 %106, label %107, label %187

; <label>:107                                     ; preds = %101
  %108 = load i8** %4, align 8
  %109 = icmp eq i8* %108, bitcast (%struct.ctk_button* @button0 to i8*)
  br i1 %109, label %110, label %111

; <label>:110                                     ; preds = %107
  call void @add_to_input(i8 signext 48)
  br label %186

; <label>:111                                     ; preds = %107
  %112 = load i8** %4, align 8
  %113 = icmp eq i8* %112, bitcast (%struct.ctk_button* @button1 to i8*)
  br i1 %113, label %114, label %115

; <label>:114                                     ; preds = %111
  call void @add_to_input(i8 signext 49)
  br label %185

; <label>:115                                     ; preds = %111
  %116 = load i8** %4, align 8
  %117 = icmp eq i8* %116, bitcast (%struct.ctk_button* @button2 to i8*)
  br i1 %117, label %118, label %119

; <label>:118                                     ; preds = %115
  call void @add_to_input(i8 signext 50)
  br label %184

; <label>:119                                     ; preds = %115
  %120 = load i8** %4, align 8
  %121 = icmp eq i8* %120, bitcast (%struct.ctk_button* @button3 to i8*)
  br i1 %121, label %122, label %123

; <label>:122                                     ; preds = %119
  call void @add_to_input(i8 signext 51)
  br label %183

; <label>:123                                     ; preds = %119
  %124 = load i8** %4, align 8
  %125 = icmp eq i8* %124, bitcast (%struct.ctk_button* @button4 to i8*)
  br i1 %125, label %126, label %127

; <label>:126                                     ; preds = %123
  call void @add_to_input(i8 signext 52)
  br label %182

; <label>:127                                     ; preds = %123
  %128 = load i8** %4, align 8
  %129 = icmp eq i8* %128, bitcast (%struct.ctk_button* @button5 to i8*)
  br i1 %129, label %130, label %131

; <label>:130                                     ; preds = %127
  call void @add_to_input(i8 signext 53)
  br label %181

; <label>:131                                     ; preds = %127
  %132 = load i8** %4, align 8
  %133 = icmp eq i8* %132, bitcast (%struct.ctk_button* @button6 to i8*)
  br i1 %133, label %134, label %135

; <label>:134                                     ; preds = %131
  call void @add_to_input(i8 signext 54)
  br label %180

; <label>:135                                     ; preds = %131
  %136 = load i8** %4, align 8
  %137 = icmp eq i8* %136, bitcast (%struct.ctk_button* @button7 to i8*)
  br i1 %137, label %138, label %139

; <label>:138                                     ; preds = %135
  call void @add_to_input(i8 signext 55)
  br label %179

; <label>:139                                     ; preds = %135
  %140 = load i8** %4, align 8
  %141 = icmp eq i8* %140, bitcast (%struct.ctk_button* @button8 to i8*)
  br i1 %141, label %142, label %143

; <label>:142                                     ; preds = %139
  call void @add_to_input(i8 signext 56)
  br label %178

; <label>:143                                     ; preds = %139
  %144 = load i8** %4, align 8
  %145 = icmp eq i8* %144, bitcast (%struct.ctk_button* @button9 to i8*)
  br i1 %145, label %146, label %147

; <label>:146                                     ; preds = %143
  call void @add_to_input(i8 signext 57)
  br label %177

; <label>:147                                     ; preds = %143
  %148 = load i8** %4, align 8
  %149 = icmp eq i8* %148, bitcast (%struct.ctk_button* @cbutton to i8*)
  br i1 %149, label %150, label %151

; <label>:150                                     ; preds = %147
  call void @clear_input()
  br label %176

; <label>:151                                     ; preds = %147
  %152 = load i8** %4, align 8
  %153 = icmp eq i8* %152, bitcast (%struct.ctk_button* @calcbutton to i8*)
  br i1 %153, label %154, label %155

; <label>:154                                     ; preds = %151
  call void @calculate()
  br label %175

; <label>:155                                     ; preds = %151
  %156 = load i8** %4, align 8
  %157 = icmp eq i8* %156, bitcast (%struct.ctk_button* @addbutton to i8*)
  br i1 %157, label %158, label %159

; <label>:158                                     ; preds = %155
  call void @input_to_operand1()
  store i8 1, i8* @op, align 1
  br label %174

; <label>:159                                     ; preds = %155
  %160 = load i8** %4, align 8
  %161 = icmp eq i8* %160, bitcast (%struct.ctk_button* @subbutton to i8*)
  br i1 %161, label %162, label %163

; <label>:162                                     ; preds = %159
  call void @input_to_operand1()
  store i8 2, i8* @op, align 1
  br label %173

; <label>:163                                     ; preds = %159
  %164 = load i8** %4, align 8
  %165 = icmp eq i8* %164, bitcast (%struct.ctk_button* @mulbutton to i8*)
  br i1 %165, label %166, label %167

; <label>:166                                     ; preds = %163
  call void @input_to_operand1()
  store i8 3, i8* @op, align 1
  br label %172

; <label>:167                                     ; preds = %163
  %168 = load i8** %4, align 8
  %169 = icmp eq i8* %168, bitcast (%struct.ctk_button* @divbutton to i8*)
  br i1 %169, label %170, label %171

; <label>:170                                     ; preds = %167
  call void @input_to_operand1()
  store i8 4, i8* @op, align 1
  br label %171

; <label>:171                                     ; preds = %170, %167
  br label %172

; <label>:172                                     ; preds = %171, %166
  br label %173

; <label>:173                                     ; preds = %172, %162
  br label %174

; <label>:174                                     ; preds = %173, %158
  br label %175

; <label>:175                                     ; preds = %174, %154
  br label %176

; <label>:176                                     ; preds = %175, %150
  br label %177

; <label>:177                                     ; preds = %176, %146
  br label %178

; <label>:178                                     ; preds = %177, %142
  br label %179

; <label>:179                                     ; preds = %178, %138
  br label %180

; <label>:180                                     ; preds = %179, %134
  br label %181

; <label>:181                                     ; preds = %180, %130
  br label %182

; <label>:182                                     ; preds = %181, %126
  br label %183

; <label>:183                                     ; preds = %182, %122
  br label %184

; <label>:184                                     ; preds = %183, %118
  br label %185

; <label>:185                                     ; preds = %184, %114
  br label %186

; <label>:186                                     ; preds = %185, %110
  call void @ctk_widget_redraw(%struct.ctk_widget* bitcast (%struct.ctk_label* @inputlabel to %struct.ctk_widget*))
  br label %198

; <label>:187                                     ; preds = %101
  %188 = load i8* %3, align 1
  %189 = zext i8 %188 to i32
  %190 = load i8* @ctk_signal_window_close, align 1
  %191 = zext i8 %190 to i32
  %192 = icmp eq i32 %189, %191
  br i1 %192, label %193, label %197

; <label>:193                                     ; preds = %187
  %194 = load i8** %4, align 8
  %195 = icmp eq i8* %194, bitcast (%struct.ctk_window* @window to i8*)
  br i1 %195, label %196, label %197

; <label>:196                                     ; preds = %193
  call void @calc_quit()
  br label %197

; <label>:197                                     ; preds = %196, %193, %187
  br label %198

; <label>:198                                     ; preds = %197, %186
  br label %199

; <label>:199                                     ; preds = %198, %100
  br label %14

; <label>:200                                     ; preds = %8
  store i8 0, i8* %PT_YIELD_FLAG, align 1
  %201 = load %struct.pt** %2, align 8
  %202 = getelementptr inbounds %struct.pt* %201, i32 0, i32 0
  store i16 0, i16* %202, align 2
  store i8 3, i8* %1
  br label %203

; <label>:203                                     ; preds = %200, %22
  %204 = load i8* %1
  ret i8 %204
}

declare void @ctk_window_new(%struct.ctk_window*, i8 zeroext, i8 zeroext, i8*) #1

declare void @ctk_widget_add(%struct.ctk_window*, %struct.ctk_widget*) #1

; Function Attrs: nounwind uwtable
define internal void @clear_input() #0 {
  %i = alloca i8, align 1
  store i8 0, i8* %i, align 1
  br label %1

; <label>:1                                       ; preds = %9, %0
  %2 = load i8* %i, align 1
  %3 = zext i8 %2 to i64
  %4 = icmp ult i64 %3, 16
  br i1 %4, label %5, label %12

; <label>:5                                       ; preds = %1
  %6 = load i8* %i, align 1
  %7 = zext i8 %6 to i64
  %8 = getelementptr inbounds [16 x i8]* @input, i32 0, i64 %7
  store i8 32, i8* %8, align 1
  br label %9

; <label>:9                                       ; preds = %5
  %10 = load i8* %i, align 1
  %11 = add i8 %10, 1
  store i8 %11, i8* %i, align 1
  br label %1

; <label>:12                                      ; preds = %1
  ret void
}

declare void @ctk_window_open(%struct.ctk_window*) #1

; Function Attrs: nounwind uwtable
define internal void @add_to_input(i8 signext %c) #0 {
  %1 = alloca i8, align 1
  %i = alloca i8, align 1
  store i8 %c, i8* %1, align 1
  store i8 0, i8* %i, align 1
  br label %2

; <label>:2                                       ; preds = %16, %0
  %3 = load i8* %i, align 1
  %4 = zext i8 %3 to i32
  %5 = icmp slt i32 %4, 11
  br i1 %5, label %6, label %19

; <label>:6                                       ; preds = %2
  %7 = load i8* %i, align 1
  %8 = zext i8 %7 to i32
  %9 = add nsw i32 %8, 1
  %10 = sext i32 %9 to i64
  %11 = getelementptr inbounds [16 x i8]* @input, i32 0, i64 %10
  %12 = load i8* %11, align 1
  %13 = load i8* %i, align 1
  %14 = zext i8 %13 to i64
  %15 = getelementptr inbounds [16 x i8]* @input, i32 0, i64 %14
  store i8 %12, i8* %15, align 1
  br label %16

; <label>:16                                      ; preds = %6
  %17 = load i8* %i, align 1
  %18 = add i8 %17, 1
  store i8 %18, i8* %i, align 1
  br label %2

; <label>:19                                      ; preds = %2
  %20 = load i8* %1, align 1
  store i8 %20, i8* getelementptr inbounds ([16 x i8]* @input, i32 0, i64 11), align 1
  ret void
}

; Function Attrs: nounwind uwtable
define internal void @input_to_operand1() #0 {
  %m = alloca i32, align 4
  %i = alloca i8, align 1
  store i64 0, i64* @operand1, align 8
  store i32 1, i32* %m, align 4
  store i8 11, i8* %i, align 1
  br label %1

; <label>:1                                       ; preds = %32, %0
  %2 = load i8* %i, align 1
  %3 = zext i8 %2 to i32
  %4 = icmp sgt i32 %3, 7
  br i1 %4, label %5, label %37

; <label>:5                                       ; preds = %1
  %6 = load i8* %i, align 1
  %7 = zext i8 %6 to i64
  %8 = getelementptr inbounds [16 x i8]* @input, i32 0, i64 %7
  %9 = load i8* %8, align 1
  %10 = sext i8 %9 to i32
  %11 = icmp sge i32 %10, 48
  br i1 %11, label %12, label %31

; <label>:12                                      ; preds = %5
  %13 = load i8* %i, align 1
  %14 = zext i8 %13 to i64
  %15 = getelementptr inbounds [16 x i8]* @input, i32 0, i64 %14
  %16 = load i8* %15, align 1
  %17 = sext i8 %16 to i32
  %18 = icmp sle i32 %17, 57
  br i1 %18, label %19, label %31

; <label>:19                                      ; preds = %12
  %20 = load i8* %i, align 1
  %21 = zext i8 %20 to i64
  %22 = getelementptr inbounds [16 x i8]* @input, i32 0, i64 %21
  %23 = load i8* %22, align 1
  %24 = sext i8 %23 to i32
  %25 = sub nsw i32 %24, 48
  %26 = load i32* %m, align 4
  %27 = mul i32 %25, %26
  %28 = zext i32 %27 to i64
  %29 = load i64* @operand1, align 8
  %30 = add i64 %29, %28
  store i64 %30, i64* @operand1, align 8
  br label %31

; <label>:31                                      ; preds = %19, %12, %5
  br label %32

; <label>:32                                      ; preds = %31
  %33 = load i8* %i, align 1
  %34 = add i8 %33, -1
  store i8 %34, i8* %i, align 1
  %35 = load i32* %m, align 4
  %36 = mul i32 %35, 10
  store i32 %36, i32* %m, align 4
  br label %1

; <label>:37                                      ; preds = %1
  call void @clear_input()
  ret void
}

; Function Attrs: nounwind uwtable
define internal void @calculate() #0 {
  %1 = load i64* @operand1, align 8
  store i64 %1, i64* @operand2, align 8
  call void @input_to_operand1()
  %2 = load i8* @op, align 1
  %3 = zext i8 %2 to i32
  switch i32 %3, label %20 [
    i32 1, label %4
    i32 2, label %8
    i32 3, label %12
    i32 4, label %16
  ]

; <label>:4                                       ; preds = %0
  %5 = load i64* @operand2, align 8
  %6 = load i64* @operand1, align 8
  %7 = add i64 %5, %6
  store i64 %7, i64* @operand2, align 8
  br label %20

; <label>:8                                       ; preds = %0
  %9 = load i64* @operand2, align 8
  %10 = load i64* @operand1, align 8
  %11 = sub i64 %9, %10
  store i64 %11, i64* @operand2, align 8
  br label %20

; <label>:12                                      ; preds = %0
  %13 = load i64* @operand2, align 8
  %14 = load i64* @operand1, align 8
  %15 = mul i64 %13, %14
  store i64 %15, i64* @operand2, align 8
  br label %20

; <label>:16                                      ; preds = %0
  %17 = load i64* @operand2, align 8
  %18 = load i64* @operand1, align 8
  %19 = udiv i64 %17, %18
  store i64 %19, i64* @operand2, align 8
  br label %20

; <label>:20                                      ; preds = %0, %16, %12, %8, %4
  call void @operand2_to_input()
  ret void
}

declare void @ctk_widget_redraw(%struct.ctk_widget*) #1

; Function Attrs: nounwind uwtable
define internal void @calc_quit() #0 {
  call void @process_exit(%struct.process* bitcast ({ %struct.process*, i8*, i8 (%struct.pt*, i8, i8*)*, %struct.pt, i8, i8, [4 x i8] }* @calc_process to %struct.process*))
  ret void
}

declare void @process_exit(%struct.process*) #1

; Function Attrs: nounwind uwtable
define internal void @operand2_to_input() #0 {
  %i = alloca i8, align 1
  %1 = load i64* @operand2, align 8
  %2 = udiv i64 %1, 10000
  %3 = urem i64 %2, 10
  %4 = trunc i64 %3 to i8
  %5 = sext i8 %4 to i32
  %6 = add nsw i32 %5, 48
  %7 = trunc i32 %6 to i8
  store i8 %7, i8* getelementptr inbounds ([16 x i8]* @input, i32 0, i64 7), align 1
  %8 = load i64* @operand2, align 8
  %9 = udiv i64 %8, 1000
  %10 = urem i64 %9, 10
  %11 = trunc i64 %10 to i8
  %12 = sext i8 %11 to i32
  %13 = add nsw i32 %12, 48
  %14 = trunc i32 %13 to i8
  store i8 %14, i8* getelementptr inbounds ([16 x i8]* @input, i32 0, i64 8), align 1
  %15 = load i64* @operand2, align 8
  %16 = udiv i64 %15, 100
  %17 = urem i64 %16, 10
  %18 = trunc i64 %17 to i8
  %19 = sext i8 %18 to i32
  %20 = add nsw i32 %19, 48
  %21 = trunc i32 %20 to i8
  store i8 %21, i8* getelementptr inbounds ([16 x i8]* @input, i32 0, i64 9), align 1
  %22 = load i64* @operand2, align 8
  %23 = udiv i64 %22, 10
  %24 = urem i64 %23, 10
  %25 = trunc i64 %24 to i8
  %26 = sext i8 %25 to i32
  %27 = add nsw i32 %26, 48
  %28 = trunc i32 %27 to i8
  store i8 %28, i8* getelementptr inbounds ([16 x i8]* @input, i32 0, i64 10), align 1
  %29 = load i64* @operand2, align 8
  %30 = urem i64 %29, 10
  %31 = trunc i64 %30 to i8
  %32 = sext i8 %31 to i32
  %33 = add nsw i32 %32, 48
  %34 = trunc i32 %33 to i8
  store i8 %34, i8* getelementptr inbounds ([16 x i8]* @input, i32 0, i64 11), align 1
  store i8 0, i8* %i, align 1
  br label %35

; <label>:35                                      ; preds = %56, %0
  %36 = load i8* %i, align 1
  %37 = zext i8 %36 to i32
  %38 = icmp slt i32 %37, 4
  br i1 %38, label %39, label %59

; <label>:39                                      ; preds = %35
  %40 = load i8* %i, align 1
  %41 = zext i8 %40 to i32
  %42 = add nsw i32 7, %41
  %43 = sext i32 %42 to i64
  %44 = getelementptr inbounds [16 x i8]* @input, i32 0, i64 %43
  %45 = load i8* %44, align 1
  %46 = sext i8 %45 to i32
  %47 = icmp eq i32 %46, 48
  br i1 %47, label %48, label %54

; <label>:48                                      ; preds = %39
  %49 = load i8* %i, align 1
  %50 = zext i8 %49 to i32
  %51 = add nsw i32 7, %50
  %52 = sext i32 %51 to i64
  %53 = getelementptr inbounds [16 x i8]* @input, i32 0, i64 %52
  store i8 32, i8* %53, align 1
  br label %55

; <label>:54                                      ; preds = %39
  br label %59

; <label>:55                                      ; preds = %48
  br label %56

; <label>:56                                      ; preds = %55
  %57 = load i8* %i, align 1
  %58 = add i8 %57, 1
  store i8 %58, i8* %i, align 1
  br label %35

; <label>:59                                      ; preds = %54, %35
  ret void
}

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"Ubuntu clang version 3.5.2-3ubuntu1 (tags/RELEASE_352/final) (based on LLVM 3.5.2)"}
