; ModuleID = 'Add.bc'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@b = common global i32 0, align 4

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %a = alloca i32, align 4
  %d = alloca i32, align 4
  %c = alloca i32, align 4
  store i32 0, i32* %1
  store i32 5, i32* %a, align 4
  %2 = call i32 @getVal()
  store i32 %2, i32* %d, align 4
  %3 = load i32* @b, align 4
  store i32 %3, i32* %d, align 4
  %4 = load i32* %a, align 4
  %5 = load i32* @b, align 4
  %6 = add nsw i32 %4, %5
  store i32 %6, i32* %c, align 4
  ret i32 0
}

; Function Attrs: nounwind uwtable
define i32 @getVal() #0 {
  store i32 16, i32* @b, align 4
  ret i32 16
}

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"clang version 3.4 (tags/RELEASE_34/final)"}
