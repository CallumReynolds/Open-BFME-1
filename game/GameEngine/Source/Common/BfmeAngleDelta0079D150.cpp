// cl: /DNDEBUG /MD /EHs-c-
// Angle fold: wraps the first angle by one full turn when it lies below the
// second, then returns the difference. Retail reads the compiler literal
// __real@40c90fdb (2*pi); writing it as a literal, not an extern float,
// lets MSVC 7.1 reload the argument under the conditional fadd.

// ?bfmeDelta@@YAMMM@Z
float __cdecl bfmeDelta(float first, float second)
{
    if (first < second)
        first += 6.2831855f;
    return first - second;
}
