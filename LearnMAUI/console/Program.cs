// https://learn.microsoft.com/en-us/dotnet/csharp/programming-guide/file-system/how-to-write-to-a-text-file

string path = "D:\\dev\\Game\\LearnMAUI\\console\\test.txt";

async Task ExampleAsync(string path)
{
    string[] lines = System.IO.File.ReadAllLines(path);
    using StreamWriter file = new(path, append: true);

    // await File.WriteAllLinesAsync(path, lines);
    foreach (string line in lines)
    {
        await file.WriteLineAsync(line);
    }
}

string[] lines = System.IO.File.ReadAllLines(path);
foreach (string line in lines)
{
    Console.WriteLine(line);
}

await ExampleAsync(path);

foreach (string line in lines)
{
    Console.WriteLine(line);
}