import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;

class NewPage extends StatefulWidget {
  @override
  _NewPageState createState() => _NewPageState();
}

class _NewPageState extends State<NewPage> {
  // List of controllers for FA1 to FA12
  final List<TextEditingController> faControllers = List.generate(12, (index) => TextEditingController());
  
  // List of controllers for AP1 to AP12
  final List<TextEditingController> apControllers = List.generate(12, (index) => TextEditingController());

  // Fungsi untuk mengirim data ke NodeMCU
  void sendDataToESP(String name, String number, String value) async {
    String url = 'http://192.168.4.1/$name$number?value=$value'; // Ganti dengan IP dan endpoint yang sesuai
    try {
      final response = await http.get(Uri.parse(url));
      if (response.statusCode == 200) {
        ScaffoldMessenger.of(context).showSnackBar(
          SnackBar(content: Text('$name$number updated to $value')),
        );
      } else {
        ScaffoldMessenger.of(context).showSnackBar(
          SnackBar(content: Text('Failed to update $name$number')),
        );
      }
    } catch (e) {
      ScaffoldMessenger.of(context).showSnackBar(
        SnackBar(content: Text('Error: $e')),
      );
    }
  }

  // Function to increment the value of AP
  void incrementValue(int index, bool isFA) {
    setState(() {
      String currentValue = isFA ? faControllers[index].text : apControllers[index].text;
      // Always append "I" when the "+" button is pressed
      if (isFA) {
        faControllers[index].text = currentValue + 'I';
      } else {
        apControllers[index].text = currentValue + 'I';
      }
    });
  }

  // Function to decrement the value of AP
  void decrementValue(int index, bool isFA) {
    setState(() {
      String currentValue = isFA ? faControllers[index].text : apControllers[index].text;
      if (currentValue.isNotEmpty) {
        if (isFA) {
          faControllers[index].text = currentValue.substring(0, currentValue.length - 1);
        } else {
          apControllers[index].text = currentValue.substring(0, currentValue.length - 1);
        }
      }
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: Text('Control FA1-12 and AP1-12')),
      body: SingleChildScrollView( // Add scroll view for better handling of overflow
        child: Padding(
          padding: EdgeInsets.all(16.0),
          child: Column(
            children: [
              Text(
                'Enter values for FA1-12',
                style: TextStyle(fontSize: 18, fontWeight: FontWeight.bold),
              ),
              SizedBox(height: 20),
              // Create inputs for FA1 to FA12 without the + and - buttons
              for (int i = 0; i < 12; i++) ...[
                Row(
                  mainAxisAlignment: MainAxisAlignment.spaceBetween,
                  children: [
                    Text('FA${i + 1}', style: TextStyle(fontSize: 16)),
                    SizedBox(
                      width: 100,
                      child: TextField(
                        controller: faControllers[i],
                        keyboardType: TextInputType.text,
                        decoration: InputDecoration(
                          labelText: 'Value',
                          border: OutlineInputBorder(),
                        ),
                      ),
                    ),
                    ElevatedButton(
                      onPressed: () {
                        String value = faControllers[i].text;
                        sendDataToESP('FA', '${i + 1}', value);
                      },
                      child: Text('Send FA${i + 1}'),
                    ),
                  ],
                ),
                SizedBox(height: 10),
              ],
              SizedBox(height: 30), // Add some space between FA and AP sections
              Text(
                'Enter values for AP1-12',
                style: TextStyle(fontSize: 18, fontWeight: FontWeight.bold),
              ),
              SizedBox(height: 20),
              // Create inputs and buttons for AP1 to AP12
              for (int i = 0; i < 12; i++) ...[
                Row(
                  mainAxisAlignment: MainAxisAlignment.spaceBetween,
                  children: [
                    Text('AP${i + 1}', style: TextStyle(fontSize: 16)),
                    SizedBox(
                      width: 100,
                      child: TextField(
                        controller: apControllers[i],
                        keyboardType: TextInputType.text,
                        decoration: InputDecoration(
                          labelText: 'Value',
                          border: OutlineInputBorder(),
                        ),
                      ),
                    ),
                    Row(
                      children: [
                        IconButton(
                          icon: Icon(Icons.remove),
                          onPressed: () {
                            decrementValue(i, false); // Decrease AP value
                            String value = apControllers[i].text;
                            sendDataToESP('AP', '${i + 1}', value);
                          },
                        ),
                        IconButton(
                          icon: Icon(Icons.add),
                          onPressed: () {
                            incrementValue(i, false); // Increase AP value
                            String value = apControllers[i].text;
                            sendDataToESP('AP', '${i + 1}', value);
                          },
                        ),
                      ],
                    ),
                    ElevatedButton(
                      onPressed: () {
                        String value = apControllers[i].text;
                        sendDataToESP('AP', '${i + 1}', value);
                      },
                      child: Text('Send AP${i + 1}'),
                    ),
                  ],
                ),
                SizedBox(height: 10),
              ],
            ],
          ),
        ),
      ),
    );
  }
}

void main() => runApp(MaterialApp(home: NewPage()));
