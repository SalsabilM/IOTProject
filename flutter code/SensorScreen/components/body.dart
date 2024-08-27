import 'package:flutter_firebase1/user_model.dart';
import 'package:flutter/material.dart';
import 'package:flutter_firebase1/SensorScreen/components/custom_card.dart';
import 'package:provider/provider.dart';
import '../../constants.dart';
import 'dart:async';
import 'package:http/http.dart' as http;
import 'package:intl/intl.dart';

class SensorScreenBody extends StatefulWidget {
  @override
  _SensorScreenBodyState createState() => _SensorScreenBodyState();
}

class _SensorScreenBodyState extends State<SensorScreenBody> {
  @override
  Widget build(BuildContext context) {
    Size size = MediaQuery.of(context).size;
    String currentDate = DateFormat('MMMM d, yyyy').format(DateTime.now());
    final user = Provider.of<UserModel>(context);

    return SafeArea(
      child: Padding(
        padding: EdgeInsets.symmetric(horizontal: size.width * 0.05),
        child: SingleChildScrollView(
          scrollDirection: Axis.vertical,
          child: Column(
            children: [
              SizedBox(height: size.height * 0.02),
              Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                children: [
                  Icon(
                    Icons.menu,
                    size: 30,
                    color: kDarkGreyColor,
                  ),
                  Text(
                    'Home',
                    style: TextStyle(
                      color: Colors.black87,
                      fontWeight: FontWeight.bold,
                      fontSize: 20,
                    ),
                  ),
                  Container(
                    height: size.height * 0.045,
                    width: size.width * 0.095,
                    decoration: BoxDecoration(
                      color: kBgColor,
                      borderRadius: BorderRadius.circular(30),
                      boxShadow: [
                        BoxShadow(
                          color: Colors.black12,
                          blurRadius: 8,
                          offset: Offset(3, 3),
                        ),
                      ],
                    ),
                    child: Icon(
                      Icons.notifications_none,
                      color: kDarkGreyColor,
                    ),
                  )
                ],
              ),
              SizedBox(height: size.height * 0.03),
              Row(
                children: [
                  // Removed photo section
                  SizedBox(width: size.width * 0.05),
                  Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: [
                      Text(
                        currentDate,
                        style: TextStyle(
                          color: Colors.grey,
                          fontWeight: FontWeight.w600,
                          fontSize: 18,
                        ),
                      ),
                      Text(
                        'Good Morning,\n${user.name}!',
                        style: TextStyle(
                          color: Colors.black87,
                          fontWeight: FontWeight.bold,
                          fontSize: 25,
                        ),
                      ),
                    ],
                  ),
                ],
              ),
              SizedBox(height: size.height * 0.05),
              Row(
                children: [
                  Expanded(
                    child: Column(
                      crossAxisAlignment: CrossAxisAlignment.start,
                      children: [
                        Text(
                          '40°',
                          style: TextStyle(
                            fontSize: 16,
                            fontWeight: FontWeight.w600,
                            color: Colors.grey,
                          ),
                        ),
                        Text(
                          'TEMPERATURE',
                          style: TextStyle(fontSize: 16, color: Colors.grey),
                        ),
                      ],
                    ),
                  ),
                  Expanded(
                    child: Column(
                      crossAxisAlignment: CrossAxisAlignment.start,
                      children: [
                        Text(
                          '59%',
                          style: TextStyle(
                            fontSize: 16,
                            fontWeight: FontWeight.w600,
                            color: Colors.grey,
                          ),
                        ),
                        Text(
                          'HUMIDITY',
                          style: TextStyle(fontSize: 16, color: Colors.grey),
                        ),
                      ],
                    ),
                  ),
                ],
              ),
              SizedBox(height: size.height * 0.05),
              Row(
                mainAxisAlignment: MainAxisAlignment.spaceAround,
                children: [
                  CustomCard(
                    size: size,
                    icon: Icon(
                      Icons.home_outlined,
                      size: 55,
                      color: Colors.grey.shade400,
                    ),
                    title: "DOOR LUCK",
                    statusOn: "OPEN",
                    statusOff: "LOCKED",
                  ),
                  CustomCard(
                    size: size,
                    icon: Icon(
                      Icons.lightbulb_outline,
                      size: 55,
                      color: Colors.grey.shade400,
                    ),
                    title: "LIGHTS DOOR",
                    statusOn: "ON",
                    statusOff: "OFF",
                  ),
                ],
              ),
              SizedBox(height: size.height * 0.025),
              Row(
                mainAxisAlignment: MainAxisAlignment.spaceAround,
                children: [
                  CustomCard(
                    size: size,
                    icon: Icon(
                      Icons.lightbulb_outline,
                      size: 55,
                      color: Colors.grey.shade400,
                    ),
                    title: "LIGHTS ROOM",
                    statusOn: "ON",
                    statusOff: "OFF",
                  ),
                  CustomCard(
                    size: size,
                    icon: Icon(
                      Icons.lightbulb_outline,
                      size: 55,
                      color: Colors.grey.shade400,
                    ),
                    title: "LIGHTS KITCHEN",
                    statusOn: "ON",
                    statusOff: "OFF",
                  ),
                ],
              ),
              SizedBox(height: size.height * 0.025),
              Row(
                mainAxisAlignment: MainAxisAlignment.spaceAround,
                children: [
                  CustomCard(
                    size: size,
                    icon: Icon(
                      Icons.lightbulb_outline,
                      size: 55,
                      color: Colors.grey.shade400,
                    ),
                    title: "LIGHTS ROOM",
                    statusOn: "ON",
                    statusOff: "OFF",
                  ),
                  // CustomCard(
                  //   size: size,
                  //   icon: Icon(
                  //     Icons.lightbulb_outline,
                  //     size: 55,
                  //     color: Colors.grey.shade400,
                  //   ),
                  //   title: "LIGHTS ROOM",
                  //   statusOn: "ON",
                  //   statusOff: "OFF",
                  // ),
                ],
              ),
              SizedBox(height: size.height * 0.025),
              Container(
                height: 75,
                width: size.width * 0.8,
                decoration: BoxDecoration(
                  color: kBgColor,
                  borderRadius: BorderRadius.circular(20),
                  boxShadow: [
                    BoxShadow(
                      color: Colors.black12,
                      blurRadius: 8,
                      offset: Offset(3, 3),
                    ),
                    BoxShadow(
                      color: Colors.white,
                      blurRadius: 0,
                      offset: Offset(-3, -3),
                    ),
                  ],
                ),
                child: Padding(
                  padding: EdgeInsets.all(15),
                  child: Row(
                    mainAxisAlignment: MainAxisAlignment.spaceBetween,
                    children: [
                      Column(
                        crossAxisAlignment: CrossAxisAlignment.start,
                        children: [
                          Text(
                            "ADD",
                            style: TextStyle(
                              fontSize: 16,
                              fontWeight: FontWeight.bold,
                              color: Colors.black54,
                            ),
                          ),
                          Text(
                            "NEW CONTROL",
                            style: TextStyle(
                              color: Colors.black45,
                              fontWeight: FontWeight.bold,
                            ),
                          )
                        ],
                      ),
                      Icon(
                        Icons.add,
                        size: 40,
                        color: Colors.black54,
                      ),
                    ],
                  ),
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }

//   Future loadData() async {
//     String jsonString = await getJsonFromFirebaseRestAPI();
//     setState(() {
//       if (jsonString == "\"motion detected\"") {
//         showDialog<String>(
//           context: context,
//           builder: (BuildContext context) => AlertDialog(
//             title: const Text('Motion detection status:'),
//             content: const Text('The motion has detected!'),
//             actions: <Widget>[
//               TextButton(
//                 onPressed: () => Navigator.pop(context, 'OK'),
//                 child: const Text('OK'),
//               ),
//             ],
//           ),
//         );
//       }
//     });
//   }

//   @override
//   void initState() {
//     loadData();
//     super.initState();
//   }
// }

// Future<String> getJsonFromFirebaseRestAPI() async {
//   String url =
//       'https://iot-home-security-5265f-default-rtdb.firebaseio.com/status.json';
//   http.Response response = await http.get(Uri.parse(url));
//   return response.body;
}

//222222222222222222222222222222222222222222222222222222222222222222222222222222
