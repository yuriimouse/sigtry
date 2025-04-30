# sigtry
Try/Catch and Signal macros for signal processing

## catch it in code
```
Try(sig0, sig1, sig2) // for example SIGSEGV etc. all signals must be defined here
{
  // main action
}
Catch
{ 
  On(sig0) {
  {
    // action 0
  }
  On(sig1) {
  {
    // action 1
  }
  Default
  {
    // default action
  }
}
```

## process it globally
```
Signal(signame)
{
  // signal action
}
```
