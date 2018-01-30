// void parse(tokenizer, filename) {
//     char temp[BUF_SIZE];
//     while (true) {
//         tokenizer.getToken(temp);
//         if (!strcmp(temp, "positions")) {
//             parsePositions(tokenizer);
//         }
//         else if (!strcmp(temp, "normals")) {
//             parseNormals(tokenizer);
//         }
//         else if (!strcmp(temp, "skinweights")) {
//             parseNormals(tokenizer);
//         }
//         else if (!strcmp(temp, "triangles")) {
//             parseNormals(tokenizer);
//         }
//     }
// }
//
// void parsePositions(tokenizer) {
//     char temp[BUF_SIZE];
//     tokenizer.getToken(temp);
//     int posAmount = atoi(temp);
//     tokenizer.findToken("{");
//     for (int i = 0; i < posAmount; i++) {
//         getVertex(i).setPosition(loadVector(tokenizer));
//     }
//     tokenizer.findToken("}");
// }
//
// void parseNormals(tokenizer) {
//     char temp[BUF_SIZE];
//     tokenizer.getToken(temp);
//     int normAmount = atoi(temp);
//     tokenizer.findToken("{");
//     for (int i = 0; i < normAmount; i++) {
//         getVertex(i).setNormal(loadVector(tokenizer));
//     }
//     tokenizer.findToken("}");
// }
//
// void parseTriangles(tokenizer) {
//     char temp[BUF_SIZE];
//     tokenizer.getToken(temp);
//     int triAmount = atoi(temp);
//     tokenizer.findToken("{");
//     for (int i = 0; i < triAmount; i++) {
//         setTriangle(i, loadIndices(tokenizer));
//     }
//     tokenizer.findToken("}");
// }
//
// void parseSkinWeights(tokenizer) {
//     char temp[BUF_SIZE];
//     tokenizer.getToken(temp);
//     int vertAmount = atoi(temp);
//     tokenizer.findToken("{");
//     for (int i = 0; i < vertAmount; i++) {
//         tokenizer.getToken(temp);
//         int attachAmount = atoi(temp);
//         for (int j = 0; j < attachAmount; j++) {
//             int index = tokenizer.getInt();
//             float weight = tokenizer.getFloat();
//             getVertex(i).addWeight(index, weight);
//         }
//     }
//     tokenizer.findToken("}");
// }
//
// void parseBindings(tokenizer) {
//     char temp[BUF_SIZE];
//     tokenizer.getToken(temp);
//     int bindingAmount = atoi(temp);
//     tokenizer.findToken("{");
//     for (int i = 0; i < bindingAmount; i++) {
//         Matrix4f mat = loadMatrix34(tokenizer);
//         mat.inverse();
//         addInvBinding(mat);
//     }
//     tokenizer.findToken("}");
// }
